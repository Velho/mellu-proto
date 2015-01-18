#include "PlayerGraphicsComponent.h"
#include "GameObject.h"

#include <iostream>

using Proto::GameObject;
using Proto::PlayerGraphicsComponent;

void PlayerGraphicsComponent::update(GameObject &obj, sf::RenderTarget &target)
{
    // Change position if changed.
    if(obj.get_position() != last_pos)
        view.setCenter(sf::Vector2f(obj.get_position().x, 300));
    if(obj.get_size() != last_sz)
        shape.setSize(obj.get_size());

    target.setView(view);
    shape.setPosition(obj.get_position());
    target.draw(shape);

    last_pos = obj.get_position();
    last_sz = obj.get_size();
}
