#ifndef PROTO_PLAYERINPUTCOMPONENT_H
#define PROTO_PLAYERINPUTCOMPONENT_H

#include "GameObject.h"

namespace Proto {

/*!
 *\brief PlayerInputClass class
 * Implements Player gameobject's InputComponent.
 */
class PlayerInputComponent : public InputComponent {
public:
    PlayerInputComponent() :
        current_keypress{ KeyPress::None }
    { }
    ~PlayerInputComponent() { }

    // Handle some sticky event situations here.
    virtual void update(GameObject&, sf::Event&) override;

    static bool is_left() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Left); }
    static bool is_right() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Right); }
    static bool is_space() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Space); }
private:
    friend class PlayerPhysicsComponent;

    bool arrow_left{ false };
    bool arrow_right{ false };

    enum class KeyPress { Left, Right, None };

    KeyPress current_keypress;

    void set_left(sf::Event&);
    void set_right(sf::Event&);
    bool is_arrow_l() const { return arrow_left; }
    bool is_arrow_r() const { return arrow_right; }
};
}

#endif
