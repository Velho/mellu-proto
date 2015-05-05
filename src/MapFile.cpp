#include "MapFile.h"
#include "Map.h"

#include "Database.h"

namespace Proto {

struct MapObjectRow {
    int id;
    float x, y;
    float width, height;
    float angle;

    /*!
     * \brief MapObjectRow
     * Constructs MapobjectRow to represent one row of data.
     * \param _x
     * \param _y
     * \param _width
     * \param _height
     */
    MapObjectRow(float _x, float _y, float _width, float _height) :
        MapObjectRow(_x, _y, _width, _height, 0.0f)
    { }

    MapObjectRow(float _x, float _y, float _width, float _height, float _angle) :
        MapObjectRow(_x, _y, _width, _height, _angle, 0)
    { }
    MapObjectRow(float _x, float _y, float _width, float _height,
            float _angle, int _id) :
        x{ _x }, y{ _y }, width{ _width }, height{ _height },
        angle{ _angle }, id{ _id }
    { } 
    /*!
     * \brief MapObjectRow
     * Constructs RowObject out of database.
     * \param r
     */
    MapObjectRow(Query::Row r) :
        MapObjectRow(r.get_double(0), r.get_double(1),
                r.get_double(2), r.get_double(3),
                r.get_double(4), r.get_int(5))
    { }

    MapObject get_map_obj()
    {
        return MapObject(
                sf::Vector2f(width, height), 
                sf::Vector2f(x, y), angle, id);
    }
};

std::vector<std::unique_ptr<MapObject>> MapFile::load()
{
    Database db(filename);
    Query qry(db, "SELECT x, y, width, height, angle, id FROM map;");

    std::vector<std::unique_ptr<MapObject>> results;

    qry.iterate([&results](Query::Row r) {
        results.emplace_back(std::unique_ptr<MapObject>(new MapObject(MapObjectRow(r).get_map_obj())));
    }); // Iterate the results.

    return results;
}

void MapFile::save(Map &map)
{
    Database db(filename);

    db.exec("DELETE FROM map;"); // Clear the map table(Maybe not the best way...).

    std::vector<MapObject*> new_objects;
    std::ostringstream ins_sql;
    int idx{ 1 };

    for(auto &obj : map.objects) {

        if(has_index(obj.get())) {
            // Construct sql statement.
            ins_sql << "INSERT INTO map(id, x, y, width, height, angle) VALUES(";
            ins_sql << idx << ", " << obj->get_position().x << ", " << obj->get_position().y << ", ";
            ins_sql << obj->get_size().x << ", " << obj->get_size().y << ", " << obj->get_rotation() << ");";
        } else
            new_objects.push_back(obj.get());

        idx++;
    }

    insert_new_objects(new_objects, ins_sql);
    db.exec(ins_sql.str());
}

bool MapFile::has_index(MapObject *m_obj)
{
    if(m_obj->get_id() != 0)
        return true;

    return false;
}

void MapFile::insert_new_objects(std::vector<MapObject*> &map_vec, std::ostringstream &ins_sql)
{
    for(auto obj : map_vec) {
        ins_sql << "INSERT INTO map(x, y, width, height, angle) VALUES(";
        ins_sql << obj->get_position().x << ", " << obj->get_position().y << ", ";
        ins_sql << obj->get_size().x << ", " << obj->get_size().y << ", " << obj->get_rotation() << ");";
    }
}

} // Namespace Proto
