#ifndef PROTO_GAMEOBJECT_H
#define PROTO_GAMEOBJECT_H

#include <memory>
#include <SFML/Graphics.hpp>

#include "InputComponent.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"

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

    static std::unique_ptr<GameObject> create_gameobject(
            InputComponent* i,
            PhysicsComponent *p,
            GraphicsComponent *g)
    {
        return std::unique_ptr<GameObject>{ new GameObject{ i, p ,g } };
    }


    sf::Vector2f get_position() const { return position; }
    void set_position(sf::Vector2f pos) { position = pos; }

    bool is_jumping() const { return jumping; }
    void set_jumping(bool jump) { jumping = jump; }

private:
    sf::Vector2f position;

    bool jumping;

    std::unique_ptr<InputComponent> input;
    std::unique_ptr<PhysicsComponent> physics;
    std::unique_ptr<GraphicsComponent> graphics;
};
}

#endif
