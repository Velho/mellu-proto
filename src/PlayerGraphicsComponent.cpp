#include "PlayerGraphicsComponent.h"
#include "GameObject.h"

#include <iostream>

using Proto::GameObject;
using Proto::PlayerGraphicsComponent;

void PlayerGraphicsComponent::update(GameObject &obj, sf::RenderTarget &target)
{
    if(obj.getPosition() != last_pos)
        view.setCenter(sf::Vector2f(obj.getPosition().x, 300));

    target.setView(view);
    shape.setPosition(obj.getPosition());
    target.draw(shape);

    last_pos = obj.getPosition();
}
