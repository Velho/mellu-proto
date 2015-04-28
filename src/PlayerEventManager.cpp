#include "PlayerEventManager.h"

#include "World.h"
#include "PlayerPhysicsComponent.h"
#include "Event.h"
#include "Droppin.h"

#include <iostream>

namespace Proto {

PlayerEventManager::PlayerEventManager(PlayerPhysicsComponent &phy) : // TODO MSVC needs const reference?
    plr_phy{ phy }, evt_obj{ nullptr }
{
}

void PlayerEventManager::update(GameObject &gobj, World &world)
{
    apply_event_collision(gobj, world);
}

void PlayerEventManager::apply_event_collision(GameObject &gobj, World &world)
{
    for(auto &obj : world.get_evt_objects()) {
        // Documented in PhysicsComponent, 2 pixel surface. (BUG in PhysicsComponent).
        sf::FloatRect obj_rekt{ obj->get_position(), sf::Vector2f{ obj->get_size().x, 2 } };

        if(gobj.get_rect().intersects(obj_rekt)) {
            plr_phy.height = obj->get_position().y - gobj.get_size().y;
            plr_phy.is_falling = false;

            if(evt_obj != obj.get()) { // If same object dont assign.
                evt_obj = obj.get();

                trigger_event(world);
            }

            evt_coll = true;
            std::cout << "evtobj(" << plr_phy.height << ")" << std::endl;
        }
    }

    complete_event_platform();
}

void PlayerEventManager::complete_event_platform()
{
	/*
	 * Very messy if expression.
	 * evt_coll != false, evt_coll manages the collision state between player and eventobject.
	 * evt_obj == true, evt_obj is pointer to last collided evetobject.
	 * plr_phy.fall_obj != nullptr, pointer to last collided mapobject.
	 *
	 * Basically this works checking if its not currently colliding with
	 * EventObject(evt_coll) and collision happens with Mapobject(fall_obj).
	 *
	 * TODO Implement support for Double Platform.
	 */
    if(!evt_coll && evt_obj && plr_phy.fall_obj != nullptr && evt_obj->get_event() != nullptr) {
		if(evt_obj->get_event()->get_type() == Event::EventType::Platform) {
			std::cout << "Completed?" << std::endl;
			evt_obj->get_event()->set_state(Event::EventState::Completed);
			evt_obj = nullptr;
		}
	}
}

void PlayerEventManager::update_platform_behavior(GameObject &gobj, World &world)
{

}

void PlayerEventManager::trigger_event(World &world)
{
    world.get_droppin()->activate_event(evt_obj->get_event());
}

}
