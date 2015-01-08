#ifndef PROTO_MAPFILE_H
#define PROTO_MAPFILE_H

#include <string>
#include <fstream>

namespace Proto {

/**
 * \brief The MapFile class
 * MapFile object.
 *
 * - Loads up the Map files which are
 *   hard coded.
 * - Checks if the map has changed from last load.
 */
class MapFile {
public:
    MapFile(std::string fn) :
        filename{ fn }
    { }



private:
    std::string filename;
    bool changed;
};

}

#endif
