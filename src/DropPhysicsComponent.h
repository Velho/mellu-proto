#ifndef PROTO_DROPPHYSICSCOMPONENT_H
#define PROTO_DROPPHYSICSCOMPONENT_H

#include "GameObject.h"

#include <random>
#include <iostream>

namespace Proto {

class DropInputComponent;

class DropPhysicsComponent : public PhysicsComponent {
public:
    DropPhysicsComponent(DropInputComponent *in) :
        input{ in }, drop_character{ generate_char() }
    {
        std::cout << "rnd : " << get_random_t(0, 26) << std::endl;
        std::cout << "char : " << drop_character << std::endl;
    }

    ~DropPhysicsComponent() { }

    /*!
     * \brief update
     * Drop's doesn't affect the World in any matter.
     * They work as separate entity in Game world.
     */
    virtual void update(GameObject &, World &) override;

private:
    friend class DropGraphicsComponent;

    sf::Vector2f target_pos;
    sf::Keyboard::Key last_key;

    const float fall_speed{ 25.f }; ///< Drop's fall speed.

    DropInputComponent *input;
    char drop_character;

    /*!
     * Let's hope this doesnt calculate everything at compile time.
     * TODO Test this out! If doesnt work like intended => replace.
     */
    int get_random_t(int min, int max)
    {
        std::uniform_int_distribution<int> rnd_dist{ min, max };

        std::random_device rnd_dev;
        std::default_random_engine def_eng{ rnd_dev() };

        return rnd_dist(def_eng);
    }

    /*!
     * \brief generate_char
     * Use C++11 random generator to generate value for
     * drop_character aka the correct answer. This is called @ ctor
     * so let's hope it wont throw an exception as the Object
     * construction can leak.
     * \return
     * Random generated character.
     */
    char generate_char();
    /*!
     * \brief key_to_char
     * Casts sf::Keyboard::Key to char.
     * sf::Keyboard::Key is a enum with underlying type
     * of int. Basically you'll get alphabets from castin Key
     * to 'A' + X, where X is 0-25.
     * \return
     * Character according to sf::Keyboard::Key.
     */
    char key_to_char(sf::Keyboard::Key);
};

}

#endif
