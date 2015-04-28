#ifndef PROTO_GRAPHICSCOMPONENT_H
#define PROTO_GRAPHICSCOMPONENT_H

#include <SFML/Graphics/RenderTarget.hpp>

namespace Proto {

class GameObject;

/*!
 *\brief GraphicsComponent class
 *
 */
class GraphicsComponent{
public:

    virtual ~GraphicsComponent() { }
    virtual void update(GameObject&, sf::RenderTarget&) = 0;
};

}

#endif
