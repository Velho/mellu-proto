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
class GameObject : public sf::Drawable {
public:
    GameObject(InputComponent *i, PhysicsComponent *p, GraphicsComponent *g) :
        input{ i }, physics{ p }, graphics{ g }
    { }

    void handle_input(sf::Event&);
    void update(World&);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    static std::unique_ptr<GameObject> create_gameobject(
            InputComponent* i,
            PhysicsComponent *p,
            GraphicsComponent *g)
    {
        return std::unique_ptr<GameObject>{ new GameObject{ i, p ,g } };
    }

    InputComponent *get_input() { return input.get(); }
    PhysicsComponent *get_physics() { return physics.get(); }
    GraphicsComponent *get_graphics() { return graphics.get(); }


    sf::Vector2f get_position() const { return position; }
    void set_position(sf::Vector2f pos) { position = pos; }

    sf::Vector2f get_size() const { return size; }
    void set_size(sf::Vector2f sz) { size = sz; }

    sf::FloatRect get_rect() const { return sf::FloatRect(get_position(), get_size()); }

private:
    sf::Vector2f position;
    sf::Vector2f size;

    std::unique_ptr<InputComponent> input;
    std::unique_ptr<PhysicsComponent> physics;
    std::unique_ptr<GraphicsComponent> graphics;
};
}

#endif
