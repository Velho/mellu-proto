#ifndef PROTO_PLAYERPHYSICSCOMPONENT_H
#define PROTO_PLAYERPHYSICSCOMPONENT_H

#include "GameObject.h"

#include <SFML/System/Clock.hpp>

namespace Proto {

class PlayerPhysicsComponent : public PhysicsComponent {
public:
    PlayerPhysicsComponent(sf::Clock &cl) :
        fps_timer{ cl }
    { }
    ~PlayerPhysicsComponent() {}

    virtual void update(GameObject&, World&) override;

private:
    sf::Clock fps_timer;
};
}

#endif
