#include "PlayerInputComponent.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

namespace Proto {

void PlayerInputComponent::update(GameObject &obj, sf::Event &event)
{
    set_left(event);
    set_right(event);

    if(arrow_left)
        current_keypress = KeyPress::Left;

    if(arrow_right)
        current_keypress = KeyPress::Right;

    if(!is_arrow_l() && !is_arrow_r())
        current_keypress = KeyPress::None;
}

void PlayerInputComponent::set_left(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Left)
            arrow_left = true;
    } else if(event.type == sf::Event::KeyReleased) {
        if(event.key.code == sf::Keyboard::Left)
            arrow_left = false;
    }
}

void PlayerInputComponent::set_right(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Right)
            arrow_right = true;
    } else if(event.type == sf::Event::KeyReleased) {
        if(event.key.code == sf::Keyboard::Right)
            arrow_right = false;
    }
}

/*// BUGGED INPUT HANDLING
void PlayerInputComponent::update(GameObject &obj, sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed) {
        // LEFT
        if (event.key.code == sf::Keyboard::Left) {

            if(current_keypress == KeyPress::Right) {
                std::cout << "Left -> Right" << std::endl;
                current_keypress = KeyPress::Right;
            } else {
                current_keypress = KeyPress::Left;
                last_keypress = KeyPress::Left;
                std::cout << "Left KeyPress" << std::endl;
            }
        }
        // RIGHT
        if (event.key.code == sf::Keyboard::Right) {

            if(current_keypress == KeyPress::Left) {
                std::cout << "Right -> Left" << std::endl;
                current_keypress = KeyPress::Left;
            } else {
                current_keypress = KeyPress::Right;
                last_keypress = KeyPress::Right;
                std::cout << "Right KeyPress" << std::endl;
            }
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if(last_keypress == KeyPress::Left && current_keypress != KeyPress::Right)
            current_keypress = KeyPress::None;
        if(last_keypress == KeyPress::Right && current_keypress != KeyPress::Left)
            current_keypress = KeyPress::None;
    }
}
*/

}
