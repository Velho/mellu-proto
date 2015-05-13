#include "Level.h"
#include "World.h"

namespace Proto {

Level::Level() : current_map{ Maps::None }, data_dir("data/maps/")
{
    // Add maps to levels container.
    levels.emplace(std::make_pair(Maps::Proto, "proto-evt.map"));
}

void Level::select_map(std::string map)
{
    current_map = str_to_maps(map);
}

std::string Level::maps_to_str(Maps map)
{
    return levels[map]; // Return by key.
}

Level::Maps Level::str_to_maps(std::string str)
{
    for(auto lvl : levels)
        if(lvl.second == str)
            return lvl.first;

    return Maps::None; // aka Null value, no map selected.
}

std::unique_ptr<World> Level::get_world()
{
    return std::unique_ptr<World>{ new World(*this) };
}
}
