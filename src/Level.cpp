#include "Level.h"

using Proto::Level;

Level::Level() : current_map{ Maps::None }
{
    levels.emplace(std::make_pair(Maps::Proto, "proto.map"));
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
