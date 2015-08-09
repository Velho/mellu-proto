#include "PlayerGraphicsComponent.h"
#include "GameObject.h"

#include "Resources.h"

#include <iostream>

namespace Proto {

PlayerGraphicsComponent::PlayerGraphicsComponent(sf::View &v) : view{ v }
{
    //shape.setFillColor(sf::Color::Blue);
    //shape.setSize(sf::Vector2f(25, 50));
}

void PlayerGraphicsComponent::update(GameObject &obj)
{
    // Change position if changed.
    if(obj.get_position() != last_pos) {
        sf::Vector2f new_center = sf::Vector2f(obj.get_position().x, 255);
        if(new_center.x > 500)
            view.setCenter(sf::Vector2f(obj.get_position().x, 255));
    }
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
