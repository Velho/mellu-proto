#ifndef PROTO_MAP_H
#define PROTO_MAP_H

#include <string>
#include <vector>
#include <memory>

#include "MapObject.h"
#include "MapFile.h"

namespace Proto {

/**
 * \brief The Map class
 * Handles the Map specific things.
 *
 * For this prototype maps are created by hand.
 * Simple text files which are easily parsable.
 * /sa MapFile
 *
 * Maps doesn't contain any information about entities and
 * their positions. Only the structural data -> where each piece
 * goes.
 */
class Map {
public:
    Map();

    void add_object(MapObject);

    void update();
    void draw(sf::RenderTarget&);

    std::vector<MapObject> get_objects() const { return objects; }

    void save_map();
    void reload_map();

    void set_reload(bool r) { reload = r; }

    friend void MapFile::save(Map&);
private:
    std::vector<MapObject> objects;
    MapFile mapfile;

    int objsaved;
    bool reload;

    void print_info();
};

}

#endif
