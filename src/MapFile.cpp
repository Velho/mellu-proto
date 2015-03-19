#include "MapFile.h"
#include "Map.h"

#include "Database.h"

#include <sstream>

namespace Proto {

struct MapObjectRow {
    float x, y;
    float width, height;

    /*!
     * \brief MapObjectRow
     * Constructs MapobjectRow to represent one row of data.
     * \param _x
     * \param _y
     * \param _width
     * \param _height
     */
    MapObjectRow(float _x, float _y, float _width, float _height) :
        x{ _x }, y{ _y }, width{ _width }, height{ _height }
    { }

    /*!
     * \brief MapObjectRow
     * Constructs RowObject out of database.
     * \param r
     */
    MapObjectRow(Query::Row r) :
        MapObjectRow(r.get_double(0), r.get_double(1), r.get_double(2), r.get_double(3))
    { }

    MapObject get_map_obj()
    {
        return MapObject(sf::Vector2f(width, height), sf::Vector2f(x, y));
    }
};

/*
void MapFile::save(Map &map)
{
    auto objects = map.objects; // Friend method; We get access to private stuff. Though VS complains its inaccessible
    std::ofstream map_file{ filename };

    if(map_file.is_open()) {
        for(auto obj : objects) {
            map_file << obj->get_position().x << " " << obj->get_position().y << " "; // X, Y
            map_file << obj->get_size().x << " " << obj->get_size().y << "\n";
        }
    }

    map_file.close(); // Close the stream.
}*/

/*!
 * \brief MapFile::load
 * Map file structure is following(numbers represent lines; W: width, H: height),
 * 1. [X] [Y] [W] [H]
 * 2. 50 50 70 70
 * 3. ... So on and so on.
 * Basically one line is the MapFileStructure
 * \return
 * Vector of pointers  to MapObject's.
 */ /*
std::vector<MapObject*> MapFile::load()
{
    std::vector<MapObject*> map_objects;
    auto file_data = parse_lines();

    std::cout << "file_data : " <<  file_data.size() << std::endl;

    // Propaply caused by invalid map file. TODO Not handled properly.
    //if(file_data.size() == 0) {
        std::cout << "Error loading map.." << std::endl;
        std::abort();
    }//

    // Create drawable MapObjects from file data.
    for(auto obj : file_data)
        map_objects.emplace_back(new MapObject(
                                     sf::Vector2f(obj.width, obj.height),
                                     sf::Vector2f(obj.x, obj.y)));
    // Return drawable map.
    return map_objects;
} */

std::vector<std::unique_ptr<MapObject>> MapFile::load()
{
    Database db(filename);
    Query qry(db, "SELECT x, y, width, height FROM map;");

    std::vector<std::unique_ptr<MapObject>> results;

    auto l_row = [&results](Query::Row r) {
        results.emplace_back(new MapObject(MapObjectRow(r).get_map_obj()));
    };
    qry.iterate(l_row); // Iterate the results.

    return results;
}

void MapFile::save(Map &map)
{
    Database db(filename);

    db.exec("DELETE FROM map;"); // Clear the map table(Maybe not the best way...).

    for(auto &obj : map.objects) {
        std::ostringstream ins_sql;
        // Construct sql statement.
        ins_sql << "INSERT INTO map(x, y, width, height) VALUES(";
        ins_sql << obj->get_position().x << ", " << obj->get_position().y << ", ";
        ins_sql << obj->get_size().x << ", " << obj->get_size().y << ");";

        db.exec(ins_sql.str());
    }
}
} // Namespace Proto
