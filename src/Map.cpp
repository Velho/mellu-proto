#include "Map.h"

using Proto::Map;
using Proto::MapFile;
using Proto::MapObject;

std::string map_dir{ "data/maps/" };
std::vector<std::string> maps {
    map_dir + "proto.map"
};

#include <iostream>

Map::Map() : mapfile{ maps[0] }, objsaved{ 0 }
{
    std::cout << "Loading map " << maps[0] << std::endl;
    objects = mapfile.load();
}

void Map::add_object(MapObject obj)
{
    objects.push_back(obj);
}

void Map::update()
{
    reload_map();
}

void Map::draw(sf::RenderTarget &target)
{
    for(auto obj : objects)
        target.draw(obj);
}

void Map::save_map()
{
    if(objects.size() != objsaved) {
        std::cout << "Saving current map " << mapfile.getFilename() << std::endl;
        std::cout << "Objects : " << std::endl;

        print_info();

        objsaved = objects.size();
        mapfile.save(*this);
    }
}

void Map::reload_map()
{
    if(reload) {
        objects = mapfile.load();
        reload = false;
    }
}

void Map::print_info()
{
    for(auto obj : objects) {
        std::cout << "x y : " << obj.get_position().x << " " << obj.get_position().y;
        std::cout << " w h : " << obj.get_size().x << " " << obj.get_size().y << std::endl;
    }
}
