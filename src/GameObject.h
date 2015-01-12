#ifndef PROTO_GAMEOBJECT_H
#define PROTO_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "World.h"

#include <memory>

namespace Proto {

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

/**
 * @brief The GameObject class
 *
 * Shared state can be directly referenced from here or
 * let components directly reference to each other.
 * This topic has been discussed here: http://gameprogrammingpatterns.com/component.html
 */
class GameObject {
public:
    GameObject(InputComponent *i, PhysicsComponent *p, GraphicsComponent *g) :
        input{ i }, physics{ p }, graphics{ g }
    { }

    void handle_input(sf::Event&);
    void update(World&);
    void draw(sf::RenderTarget&);

    static std::unique_ptr<GameObject> create_gameobject(
            InputComponent* i,
            PhysicsComponent *p,
            GraphicsComponent *g)
    {
        return std::unique_ptr<GameObject>{ new GameObject{ i, p ,g } };
    }

private:
    sf::Vector2i position;

    std::unique_ptr<InputComponent> input;
    std::unique_ptr<PhysicsComponent> physics;
    std::unique_ptr<GraphicsComponent> graphics;
};
}

#endif
