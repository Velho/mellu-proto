#include "PlayerInputComponent.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

using Proto::GameObject;
using Proto::PlayerInputComponent;

void PlayerInputComponent::update(GameObject &obj, sf::Event& /* event */)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sf::Vector2f old{ obj.getPosition() };
        old.x += 5;

        obj.setPosition(old);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sf::Vector2f old{ obj.getPosition() };
        old.x -= 5;

        obj.setPosition(old);
    }
}
