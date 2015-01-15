#ifndef PROTO_PLAYERINPUTCOMPONENT_H
#define PROTO_PLAYERINPUTCOMPONENT_H

#include "GameObject.h"

namespace Proto {

class PlayerInputComponent : public InputComponent {
public:
    ~PlayerInputComponent() { }

    virtual void update(GameObject&, sf::Event&) override;
};
}

#endif
