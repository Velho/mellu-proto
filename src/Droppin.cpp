#include "Droppin.h"

#include "DropInputComponent.h"
#include "DropPhysicsComponent.h"
#include "DropGraphicsComponent.h"

#include "World.h"
#include "Events.h"

namespace Proto {

std::unique_ptr<GameObject> Droppin::create_drop()
{
    // Drop GameObject's components.
    DropInputComponent *input{ new DropInputComponent };
    DropPhysicsComponent *physics{ new DropPhysicsComponent(input) };
    DropGraphicsComponent *graphics{ new DropGraphicsComponent(physics) };

    return std::unique_ptr<GameObject>(new GameObject(input, physics, graphics));
}

void Droppin::handle_input(sf::Event &event)
{
    for(auto &g : drop_objs)
        g->handle_input(event);
}

void Droppin::update(World &world)
{
    for(auto &g : drop_objs)
        g->update(world);
}

void Droppin::draw(sf::RenderTarget &target)
{
    for(auto &g : drop_objs)
        g->draw(target);
}

}
