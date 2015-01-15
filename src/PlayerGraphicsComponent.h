#ifndef PROTO_PLAYERGRAPHICSCOMPONENT_H
#define PROTO_PLAYERGRAPHICSCOMPONENT_H

#include "GameObject.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace Proto {

class PlayerGraphicsComponent : public GraphicsComponent {
public:
    PlayerGraphicsComponent(sf::View &v) : view{ v }
    {
        shape.setFillColor(sf::Color::Blue);
        shape.setSize(sf::Vector2f(25, 50));
    }

    ~PlayerGraphicsComponent() { }

    virtual void update(GameObject&, sf::RenderTarget&) override;

private:
    sf::RectangleShape shape;
    sf::View &view;
    sf::Vector2f last_pos; //! Update view only if position has changed.
};
}
#endif
