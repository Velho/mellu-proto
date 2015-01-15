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

    Map *getMap() { return map.get(); }

private:
    std::unique_ptr<Map> map;
};

}

#endif
