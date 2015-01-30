#ifndef PROTO_PLAYERINPUTCOMPONENT_H
#define PROTO_PLAYERINPUTCOMPONENT_H

#include "GameObject.h"

namespace Proto {

class PlayerInputComponent : public InputComponent {
public:
    PlayerInputComponent() : last_keypress{ KeyPress::None }
    { }
    ~PlayerInputComponent() { }

    // Handle some sticky event situations here.
    virtual void update(GameObject&, sf::Event&) override;

    static bool is_left() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Left); }
    static bool is_right() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Right); }
    static bool is_space() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Space); }
private:
    const float WALK_ACCELERATION = 250;

    friend class PlayerPhysicsComponent;

    enum class KeyPress { Left, Right, None } last_keypress;
};
}

#endif
