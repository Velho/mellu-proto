#ifndef PROTO_WORLD
#define PROTO_WORLD

#include "Map.h"
#include "Events.h"
#include "Level.h"

namespace Proto {

/*!
 *\brief
 * World shows us everything that gets drawn on the screen.
 * TODO Add way to switch between worlds.
 */
class World {
public:
    World(Level&);

    void update();
    void draw(sf::RenderTarget&);

    // Interface requests to map.
    void add_map_object(MapObject);
    void save_map();
    void reload_map();
    std::vector<MapObject*> get_map_objects();
    //Map *get_map() { return current_map.get(); }

    sf::FloatRect get_rect(std::size_t) const;

private:
    std::unique_ptr<Map> current_map;
};

}

#endif
