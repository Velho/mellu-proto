#ifndef PROTO_MOVABLEPLATFORM_H
#define PROTO_MOVABLEPLATFORM_H

#include "MapObject.h"

namespace Proto {

class MovablePlatform : public MapObject {
public:

    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

private:

};

}

#endif
