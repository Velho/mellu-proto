#include "Droppin.h"

#include "DropInputComponent.h"
#include "DropPhysicsComponent.h"
#include "DropGraphicsComponent.h"

using Proto::Droppin;
using Proto::GameObject;

using Proto::DropInputComponent;
using Proto::DropPhysicsComponent;
using Proto::DropGraphicsComponent;

Droppin::GObjPtr Droppin::create_drop()
{
    // Drop GameObject's components.
    DropInputComponent *input{ new DropInputComponent };
    DropPhysicsComponent *physics{ new DropPhysicsComponent(input) };
    DropGraphicsComponent *graphics{ new DropGraphicsComponent(physics) };

    return GObjPtr{ new GameObject(input, physics, graphics) };
}

void Droppin::handle_input(sf::Event &event)
{
    for(auto &g : gobjs)
        g->handle_input(event);
}

void Droppin::update(World &world)
{
    for(auto &g : gobjs)
        g->update(world);
}

void Droppin::draw(sf::RenderTarget &target)
{
    spawn_box.setPosition(sf::Vector2f(400, 0));

    target.draw(spawn_box);

    for(auto &g : gobjs)
        g->draw(target);
}
