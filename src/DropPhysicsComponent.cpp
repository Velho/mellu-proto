#include "DropPhysicsComponent.h"
#include "DropInputComponent.h"

using Proto::GameObject;
using Proto::DropPhysicsComponent;
using Proto::World;

void DropPhysicsComponent::update(GameObject &, World &)
{
    if(last_key != input->key_pressed) { // Key's doesnt match so it's a new key.
        if(key_to_char(input->key_pressed) == drop_character)
            std::cout << "Input is a match!" << std::endl;
    }

    last_key = input->key_pressed;
}


char DropPhysicsComponent::generate_char()
{
    // Number for alphabets. 0 - 25 = 26. A = 0, B = 1, etc
    const int count_alph = 25;
    int rnd_value = get_random_t(0, count_alph);

    // C-cast works aswell.
    return key_to_char(static_cast<sf::Keyboard::Key>(rnd_value));
}

char DropPhysicsComponent::key_to_char(sf::Keyboard::Key key)
{
    return static_cast<char>('A' + key);
}
