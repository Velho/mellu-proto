#include "DropInputComponent.h"

using Proto::DropInputComponent;
using Proto::GameObject;

void DropInputComponent::update(GameObject &, sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed) {
        if(is_key_in_range(event.key.code))
            key_pressed = event.key.code;
    }
}

bool DropInputComponent::is_key_in_range(sf::Keyboard::Key key)
{
    if(key >= 0 && key <= 25)
        return true;

    return false;
}
