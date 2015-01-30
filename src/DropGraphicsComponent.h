#ifndef PROTO_DROPGRAPHICSCOMPONENT_H
#define PROTO_DROPGRAPHICSCOMPONENT_H

#include "GameObject.h"

namespace Proto {

class DropPhysicsComponent;

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
        target_shape.setOutlineColor(sf::Color::White); // TODO Must depend on the background coloring.
        target_shape.setFillColor(sf::Color::Transparent); // Transparent fill.

        init_text();
    }
    ~DropGraphicsComponent() { }

    virtual void update(GameObject &, sf::RenderTarget &) override;
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
