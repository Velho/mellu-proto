#ifndef PROTO_WORLD
#define PROTO_WORLD

#include "Level.h"

#include "MapObject.h"
#include "EventObject.h"

namespace Proto {

class Map;
class Events;

/*!
 *\brief
 * World shows us everything that gets drawn on the screen.
 * TODO Add way to switch between worlds.
 */
class World {
public:
    World(Level&);
    ~World();

    void update();
    void draw(sf::RenderTarget&);

    // Interface requests to map.
    void add_map_object(MapObject);
    void save_map();
    void reload_map();
    std::vector<std::unique_ptr<MapObject>> &get_map_objects();

    // Interface for events.
    void add_evt_object(EventObject);
    void save_evt();

    sf::FloatRect get_rect(std::size_t) const;

private:
    std::unique_ptr<Map> current_map;
    std::unique_ptr<Events> current_evts;
};

}

#endif
