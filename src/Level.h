#ifndef PROTO_LEVEL_H
#define PROTO_LEVEL_H

#include <map>
#include <string>
#include <memory>

namespace Proto {

class World;

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
    std::string get_current_map_str() { return data_dir + levels[current_map]; }

    /*!
     *\brief get_world
     * Constructs new World unique_ptr for map & event usage.
     * Assign from this when new Map is selected.
     *\return
     * unique_ptr<World> Smart pointer to heap allocated memory of class World.
     */
    std::unique_ptr<World> get_world();

private:
    std::map<Maps, std::string> levels;
    Maps current_map;
    const std::string data_dir;

    std::string maps_to_str(Maps); ///< Returns string representation of the enum class.
    Maps str_to_maps(std::string); ///< Returns enum class Maps representation of std::string.
};
}

#endif

