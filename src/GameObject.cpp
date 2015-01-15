#include "GameObject.h"

using Proto::GameObject;
using Proto::World;

void GameObject::handle_input(sf::Event &event)
{
    input->update(*this, event);
}

void GameObject::update(World &world)
{
    physics->update(*this, world);
}

void GameObject::draw(sf::RenderTarget &target)
{
    graphics->update(*this, target);
}
