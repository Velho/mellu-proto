#include "Map.h"

using Proto::Map;
using Proto::MapFile;
using Proto::MapObject;

#include <iostream>

const std::string map_data_dir("data/maps/");

Map::Map(std::string file) : mapfile(map_data_dir + file), objsaved{ 0 }, reload{ false }
{
    std::cout << "Loading map " << file << std::endl;
    objects = std::move(mapfile.load());
}

Map::~Map()
{}

void Map::add_object(MapObject obj)
{
    objects.emplace_back(new MapObject(obj));
}

void Map::update()
{
    reload_map();
}

void Map::draw(sf::RenderTarget &target)
{
    for(auto &obj : objects)
        target.draw(*obj);
}

void Map::save_map()
{
    // If there's new or removed objects => Save the map.
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
    // Let's keep this simple. Reload when reload is true.
    if(reload) {
        objects = mapfile.load();
        reload = false;
    }
}

void Map::print_info()
{
    for(auto &obj : objects) {
        std::cout << "x y : " << obj->get_position().x << " " << obj->get_position().y;
        std::cout << " w h : " << obj->get_size().x << " " << obj->get_size().y << std::endl;
    }
}
