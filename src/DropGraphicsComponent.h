#ifndef PROTO_DROPGRAPHICSCOMPONENT_H
#define PROTO_DROPGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Proto {

class DropPhysicsComponent;
class GameObject;

/**
 * \brief The DropGraphicsComponent class
 *  As DropGraphicsComponent defines 2 drawable
 *  shapes.
 */
class DropGraphicsComponent : public GraphicsComponent {
public:
    DropGraphicsComponent(DropPhysicsComponent *ph) :
        physics{ ph }, drop_shape{ 15 }, target_shape{ 15 }
    {
        // TODO Must depend on the background coloring.
        target_shape.setOutlineColor(sf::Color::White); 
        target_shape.setFillColor(sf::Color::Transparent); // Transparent fill.

        init_text();
    }
    ~DropGraphicsComponent() { }

    virtual void update(GameObject &) override;
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    sf::CircleShape drop_shape;
    sf::CircleShape target_shape;
    //sf::Vector2f last_pos;
    sf::Text letter;

    void init_text();

    DropPhysicsComponent *physics; ///< Mainly for positions, etc.
};

}

#endif
