#include "PlayerInputComponent.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

using Proto::GameObject;
using Proto::PlayerInputComponent;

void PlayerInputComponent::update(GameObject &obj, sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Left)
            last_keypress = KeyPress::Left;
        if(event.key.code == sf::Keyboard::Right)
            last_keypress = KeyPress::Right;
    }

}
