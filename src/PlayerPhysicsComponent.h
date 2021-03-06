#ifndef PROTO_PLAYERPHYSICSCOMPONENT_H
#define PROTO_PLAYERPHYSICSCOMPONENT_H

#include "PlayerInputComponent.h"
#include "PlayerEventManager.h"

#include <SFML/System/Clock.hpp>

#include <iostream>

namespace Proto {

class PlayerInputComponent;
class MapObject;

//class BoundingBox;

enum class PlayerState {
    StandingLeft,
    StandingRight,
    Standing,
    RunningLeft,
    RunningRight,
    Jumping,
    Falling
};

/*!
 * \brief The PlayerPhysicsComponent class
 * Calculated player specific physics, collisions,
 * movement, jumping, etc.
 */
class PlayerPhysicsComponent : public PhysicsComponent {
public:
    PlayerPhysicsComponent(PlayerInputComponent *in) :
        input_cmp{ in },
        is_falling{ false },
        current_state{ PlayerState::Falling },
        fall_obj{ nullptr },
        evt_mgr{ *this }
    {
		init_fall(); // Let's fall in to the game ehehehe
    }
    ~PlayerPhysicsComponent() {}

    //! Updates PlayerPhysicsComponents state every frame.
    virtual void update(GameObject&, World&) override;

    void reset();   ///< Resets fall variables. Prevents glitch.

private:
    friend class PlayerEventManager;
    friend class AnimatedPlayer; // Player Animator Object

    PlayerState current_state;
    MapObject *fall_obj;

    PlayerInputComponent *input_cmp;
    PlayerEventManager evt_mgr;

    bool is_falling;

    float multiplier_gravity;
    float jump_speed;
    float fall_speed;

    // Calculated height where we hit collision
    float height;

    sf::Vector2f velocity; ///< Modify player's movement velocity.

    const float WALK_ACCELERATION = 5;

    void set_state();               ///< Sets current_state according to input.
    bool check_state(PlayerState);  ///< Checks if current_state is new_state, returns true if equals.
    bool is_falling_or_jumping();   ///< Returns true if current_state is PlayerState::Jumping or PlayerState::Falling.
    void add_velocity();            ///< Adds velocity according to input.
    void set_standing();

    bool is_slope(MapObject&);      ///< Checks if the mapobject has rotation.
    //void calculate_slope_velocity(GameObject&, BoundingBox&);///< Calculate velocity in slopes.

    void apply_gravity(GameObject&, World&);        ///< Applies simulated gravity on state PlayerState::Falling.
    void apply_fall_collision(GameObject&, World&); ///< Calculate collision when PlayerState::Falling.

    //! Calculates collision when PlayerState::RunningLeft & PlayerState::Right.
    //! Also inits falling when player moves out of the fall_obj.
    //! \sa MapObject *fall_obj
    void apply_map_collision(GameObject&, World&);
    void apply_event_collision(GameObject&, World&);

    //void apply_slope_collision(GameObject&, MapObject&);

    void init_fall(); ///< Initializes fall variables; fall_speed, is_falling. Cannot be called if is_falling == true.
    void init_jump(); ///< Initializes

    void do_jumping(GameObject&);   ///< Calculates jumping.
    void do_movement(GameObject&);  ///< Calculates movement.

    void print_state();             ///< DEBUG function, prints out some variables into cout.
};
}

#endif
