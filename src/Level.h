#ifndef PROTO_LEVEL_H
#define PROTO_LEVEL_H

#include <map>
#include <string>

namespace Proto {

/*!
 *\brief
 * Level abstractions. Holds up different level information.
 * Provides enum's and strings to correct level files.
 *
 * This class operates as manager class for ease
 * level selection, changing, modding, etc. 
 */
class Level {
public:
    Level();

    /// Lists all available Maps to use.
    enum class Maps {
        None, ///< No map selected.
        Proto ///< Current test map.
    };

    /*!
     *\brief
     * Assign new current map.
     *\param enum class Maps
     * Selected Map from enum class.
     */
    void select_map(Maps map) { current_map = map; }
    /*!
     *\brief
     * Assign new current map(overload).
     *\param std::string
     * Converts str into enum class Maps and assigns new map.
     */
    void select_map(std::string);

    Maps get_current_map() const { return current_map; }
    std::string get_current_map_str() { return levels[current_map]; }



private:
    std::map<Maps, std::string> levels;
    Maps current_map;

    std::string maps_to_str(Maps); ///< Returns string representation of the enum class.
    Maps str_to_maps(std::string); ///< Returns enum class Maps representation of std::string.
};
}

#endif

