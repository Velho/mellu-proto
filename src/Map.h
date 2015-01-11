#ifndef PROTO_MAP_H
#define PROTO_MAP_H

#include <string>
#include <vector>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>

#include "MapObject.h"

namespace Proto {

class MapFile;

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
private:
    std::vector<MapObject> objects;
    //std::unique_ptr<MapFile> mapfile;

};

}

#endif
