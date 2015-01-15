#ifndef PROTO_GAMEOBJECT_H
#define PROTO_GAMEOBJECT_H

#include <memory>
#include <SFML/Graphics.hpp>

#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"

namespace Proto {

class World;

/**
 * @brief The GameObject class
 *
 * Shared state can be directly referenced from here or
 * let components directly reference to each other.
 * This topic has been discussed here: http://gameprogrammingpatterns.com/component.html
 *
 */
class GameObject {
public:
    GameObject(InputComponent *i, PhysicsComponent *p, GraphicsComponent *g) :
        input{ i }, physics{ p }, graphics{ g }
    { }

    void handle_input(sf::Event&);
    void update(World&);
    void draw(sf::RenderTarget&);

    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getSize() const { return size; }

    void setPosition(sf::Vector2f pos) { position = pos; }
    void setSize(sf::Vector2f sz) { size = sz; }

private:
    sf::Vector2f position;
    sf::Vector2f size;

    std::unique_ptr<InputComponent> input;
    std::unique_ptr<PhysicsComponent> physics;
    std::unique_ptr<GraphicsComponent> graphics;
};
}

#endif
