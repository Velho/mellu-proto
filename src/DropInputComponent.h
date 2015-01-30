#ifndef PROTO_DROPINPUTCOMPONENT_H
#define PROTO_DROPINPUTCOMPONENT_H

#include "GameObject.h"

namespace Proto {

/**
 * \brief The DropInputComponent class
 */
class DropInputComponent : public InputComponent {
public:

    virtual void update(GameObject &, sf::Event &) override;
private:
    friend class DropPhysicsComponent;
    sf::Keyboard::Key key_pressed;

    ///< Checks if Key is in range of alphabets. 0 - 25
    bool is_key_in_range(sf::Keyboard::Key);
};

}

#endif
