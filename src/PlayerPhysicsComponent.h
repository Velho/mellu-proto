#ifndef PROTO_PLAYERPHYSICSCOMPONENT_H
#define PROTO_PLAYERPHYSICSCOMPONENT_H

#include "GameObject.h"
#include "PlayerInputComponent.h"
#include "World.h"

#include <SFML/System/Clock.hpp>

#include <iostream>

namespace Proto {

class PlayerPhysicsComponent : public PhysicsComponent {
public:
    PlayerPhysicsComponent(sf::Clock &cl) :
        is_falling{ true }, current_state{ PlayerState::Falling }, timer{ cl }
    {
    }
    ~PlayerPhysicsComponent() {}

    enum class PlayerState {
        Standing,
        RunningLeft,
        RunningRight,
        Jumping,
        Falling
    };

    virtual void update(GameObject&, World&) override;

private:
    sf::Clock &timer;
    PlayerState current_state;


    bool is_falling;

    float multiplier_gravity;
    float fall_speed;

    // Calculated height where we hit collision
    float height;

    const float WALK_ACCELERATION = 5;

    void set_state();
    bool check_state(PlayerState);
    bool is_falling_or_jumping();

    void apply_gravity(GameObject&, World&);
    void apply_fall_collision(GameObject&, World&);
    void apply_map_collision(GameObject&, World&);

    void init_fall();
    void init_jump();

    void do_jumping(GameObject&);
    void do_movement(GameObject&);

    void print_state();
};
}

#endif
