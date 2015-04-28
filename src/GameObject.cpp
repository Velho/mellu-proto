#include "GameObject.h"

namespace Proto {

void GameObject::handle_input(sf::Event &event)
{
    input->update(*this, event);
}

void GameObject::update(World &world)
{
    physics->update(*this, world);
}

void GameObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    /*
     * const_cast<T>(..) explained..
     * Drawing is done in 2 parts. 
     * Updating some Rendering logic and rendering.
     * System was originally designed by fusing these two
     * procedures as one, but as the system evolved it was
     * required to split these two up.
     * Examples:
     *\sa PlayerGraphicsComponent class
     *\sa DropGraphicsComponent class
     */
    graphics->update(const_cast<GameObject&>(*this));

    target.draw(*graphics);
}

}
