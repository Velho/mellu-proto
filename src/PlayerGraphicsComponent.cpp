#include "PlayerGraphicsComponent.h"
#include "GameObject.h"

#include <iostream>

namespace Proto {

void PlayerGraphicsComponent::update(GameObject &obj)
{
    // Change position if changed.
    if(obj.get_position() != last_pos)
        view.setCenter(sf::Vector2f(obj.get_position().x, 300));
    if(obj.get_size() != last_sz)
        shape.setSize(obj.get_size());

    shape.setPosition(obj.get_position());

    last_pos = obj.get_position();
    last_sz = obj.get_size();
}

void PlayerGraphicsComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.setView(view);
    target.draw(shape);
}
}
