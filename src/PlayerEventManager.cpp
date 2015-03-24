#include "PlayerEventManager.h"

#include "World.h"
#include "PlayerPhysicsComponent.h"

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

            evt_obj = obj.get();
            std::cout << "evtobj(" << plr_phy.height << ")" << std::endl;
        }
    }
}

}
