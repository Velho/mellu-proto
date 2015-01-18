#ifndef PROTO_WORLD
#define PROTO_WORLD

#include "Map.h"

namespace Proto {

class World {
public:
    World() : map{ new Map() }
    { }

    void update();
    void draw(sf::RenderTarget&);

    Map *get_map() { return map.get(); }

    sf::FloatRect get_rect(std::size_t) const;

private:
    std::unique_ptr<Map> map;
};

}

#endif
