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
    Map() { }

    void addObject(MapObject);

    void update();
    void draw(sf::RenderTarget&);

    friend void MapFile::save(Map&);
private:
    std::vector<MapObject> objects;
    //std::unique_ptr<MapFile> mapfile;

};

}

#endif
