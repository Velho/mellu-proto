#include "World.h"

#include "Map.h"
#include "Events.h"

#include "Droppin.h"

namespace Proto {

World::World(Level &level)
{
    current_map = std::unique_ptr<Map>{ new Map(level.get_current_map_str()) };
    current_evts = std::unique_ptr<Events>{ new Events(level.get_current_map_str()) };
}

World::~World()
{

}

void World::update()
{
    current_map->update();
    current_evts->update(*this);
}

void World::draw(sf::RenderTarget &target)
{
    current_map->draw(target);
    current_evts->draw(target);
}

sf::FloatRect World::get_rect(std::size_t idx) const
{
    return current_map->get_objects()[idx]->get_frect();
}

/** Interfacing Map class **/

void World::add_map_object(MapObject obj)
{
    current_map->add_object(obj);
}

void World::save_map()
{
    current_map->save_map();
}

void World::reload_map()
{
    current_map->set_reload(true);
}

std::vector<std::unique_ptr<MapObject>> &World::get_map_objects()
{
    return current_map->get_objects();
}

std::vector<EventObject::EvtObjectPtr> &World::get_evt_objects()
{
    return current_evts->get_evt_objects();
}

void World::add_event_object(EventObject obj)
{
    current_evts->add_event_obj(obj);
}

void World::save_events()
{
    current_evts->save_objs();
}

Droppin *World::get_droppin()
{
	return current_evts->get_droppin();
}

MapObject *World::get_mobj_by_idx(std::size_t idx)
{
    return current_map->get_by_idx(idx);
}

EventObject *World::get_eobj_by_idx(std::size_t idx)
{
    return current_evts->get_by_idx(idx);
}

}
