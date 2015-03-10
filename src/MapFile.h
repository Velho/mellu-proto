#ifndef PROTO_MAPFILE_H
#define PROTO_MAPFILE_H

#include <string>
#include <vector>
#include <memory>

namespace Proto {

class Map;
class MapObject;

/**
 * \brief The MapFile class
 * MapFile object.
 *
 * - Loads up the Map files which are
 *   hard coded.
 * - Checks if the map has changed from last load.
 * - Current implementation overwrites everything.
 *   Basically for sqlite based table we could delete
 *   the data and rewrite. Then it would not affect any
 *   other part of the program.
 *
 *
 */
class MapFile {
public:
    MapFile(std::string fn) :
        filename( fn )
    { }

    void save(Map&);
    friend void save(Map&);

    /*!
     * \brief MapFile::load
     * Map file structure is following(numbers represent lines; W: width, H: height),
     * 1. [X] [Y] [W] [H]
     * 2. 50 50 70 70
     * 3. ... So on and so on.
     * Basically one line is the MapFileStructure
     * \return
     * Vector of pointers  to MapObject's.
     */
    std::vector<std::unique_ptr<MapObject>> load();

    std::string getFilename() const { return filename; }

private:
    std::string filename;
    bool changed;
};

}

#endif
