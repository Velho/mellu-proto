#ifndef PROTO_GRAPHICSCOMPONENT_H
#define PROTO_GRAPHICSCOMPONENT_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace Proto {

class GameObject;

/*!
 *\brief GraphicsComponent class
 *
 */
class GraphicsComponent : public sf::Drawable {
public:

    virtual ~GraphicsComponent() { }
    virtual void update(GameObject&) { };
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const { };

    virtual void set_texture(sf::Texture*) { };
};

}

#endif
