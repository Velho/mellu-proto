#include "Map.h"

using Proto::Map;
//using Proto::MapFile;
using Proto::MapObject;

std::string map_dir{ "data/maps/" };
std::vector<std::string> maps {
    map_dir + "proto.map"
};


void Map::addObject(MapObject obj)
{
    objects.push_back(obj);
}

void Map::update()
{

}

void Map::draw(sf::RenderTarget &target)
{
    for(auto obj : objects)
        target.draw(obj);
}

