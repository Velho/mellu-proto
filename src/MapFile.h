#ifndef PROTO_MAPFILE_H
#define PROTO_MAPFILE_H

#include <string>
#include <vector>

namespace Proto {

class Map;
class MapObject;

struct MapFileStructure;

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
        filename( fn )
    { }

    void save(Map&);
    friend void save(Map&);

    std::vector<MapObject*> load();

    std::string getFilename() const { return filename; }

private:
    std::string filename;
    bool changed;

    std::vector<MapFileStructure> parse_lines();
};

}

#endif
