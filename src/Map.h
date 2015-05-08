#ifndef PROTO_MAP_H
#define PROTO_MAP_H

#include "MapObject.h"
#include "MapFile.h"

namespace Proto {

/**
 * \brief The Map class
 * Handles the Map specific things.
 *
 * For this prototype maps are created by hand.
 * Simple database table which are easily parsable.
 * /sa MapFile
 *
 * Maps doesn't contain any information about entities and
 * their positions. Only the structural data -> where each piece
 * goes.
 */
class Map {
public:
    Map(std::string file);
    ~Map();

    /*!
     *\brief
     * Adds new MapObject into objects container.
     * This method is primarily used from the Editor
     * so it also manages the index for table.
     */
    void add_object(MapObject);

    void update();
    void draw(sf::RenderTarget&);

    std::vector<std::unique_ptr<MapObject>> &get_objects() { return objects; }

    void save_map();
    void reload_map();

    void set_reload(bool r) { reload = r; }

    friend void MapFile::save(Map&);
private:
    std::vector<std::unique_ptr<MapObject>> objects;
    MapFile mapfile;

    int objsaved;
    bool reload;

    void print_info();
};

}

#endif
