#include "MapFile.h"
#include "Map.h"

#include <sstream>
#include <fstream>

#include<iostream>

// Add namespaces for Map specific stuff.
using Proto::Map;
using Proto::MapFile;
using Proto::MapObject;

//using Proto::MapFileStructure;

struct Proto::MapFileStructure {
    float x, y;
    float width, height;
};

void MapFile::save(Map &map)
{
    auto objects = map.objects; // Friend method; We get access to private stuff. Though VS complains its inaccessible
    std::ofstream map_file{ filename };

    if(map_file.is_open()) {
        for(auto obj : objects) {
            map_file << obj.get_position().x << " " << obj.get_position().y << " "; // X, Y
            map_file << obj.get_size().x << " " << obj.get_size().y << "\n";
        }
    }

    map_file.close(); // Close the stream.
}

/**
 * @brief MapFile::load
 * Map file structure is following(numbers represent lines; W: width, H: height),
 * 1. [X] [Y] [W] [H]
 * 2. 50 50 70 70
 * 3. ... So on and so on.
 * Basically one line is the MapFileStructure
 * @return
 */
std::vector<MapObject> MapFile::load()
{
    std::vector<MapObject> map_objects;
    auto file_data = parse_lines();

    std::cout << "file_data : " <<  file_data.size() << std::endl;

    // Propaply caused by invalid map file. TODO Not handled properly.
    /*if(file_data.size() == 0) {
        std::cout << "Error loading map.." << std::endl;
        std::abort();
    }*/

    // Create drawable MapObjects from file data.
    for(auto obj : file_data)
        map_objects.emplace_back(MapObject(
                                     sf::Vector2f(obj.width, obj.height),
                                     sf::Vector2f(obj.x, obj.y)));
    // Return drawable map.
    return map_objects;
}

std::vector<Proto::MapFileStructure> MapFile::parse_lines()
{
    std::ifstream map_stream(filename);
    std::vector<MapFileStructure> results;

    if(map_stream.is_open()) { // File is open, lets parseee.
        std::string line;

        std::cout << "Stream is open" << std::endl;

        while(std::getline(map_stream, line)) {
            std::istringstream temp_line{ line }; // For data parsing.
            MapFileStructure temp_map;

            std::cout << line << std::endl;

            // Let's parse the line;
            if(!(temp_line >> temp_map.x >> temp_map.y >> temp_map.width >> temp_map.height))
                break; // Error. TODO Maybe handle this.. ABBORT ABBORT

            // Push the results.
            results.emplace_back(temp_map);
        }
    }

    //map_stream.close(); // Close the stream.
    return results;
}
