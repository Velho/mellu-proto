#include "World.h"

#include "Map.h"
#include "Events.h"

using Proto::World;
using Proto::Events;
using Proto::Level;
using Proto::Map;
using Proto::MapObject;

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
}

void World::draw(sf::RenderTarget &target)
{
    current_map->draw(target);
}

sf::FloatRect World::get_rect(std::size_t idx) const
{
    return current_map->get_objects()[idx]->get_frect();
}

/** Interfacing Map class **/

void World::add_map_object(Proto::MapObject obj)
{
    current_map->add_object(Proto::MapObject(obj));
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
