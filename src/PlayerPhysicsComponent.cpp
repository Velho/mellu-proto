#include "PlayerPhysicsComponent.h"

using Proto::PlayerPhysicsComponent;
using Proto::GameObject;
using Proto::World;

using input = Proto::PlayerInputComponent;

void PlayerPhysicsComponent::print_state()
{
    if(current_state == PlayerState::Falling)
        std::cout << "State : Falling" << std::endl;
    if(current_state == PlayerState::Jumping)
        std::cout << "State : Jumping" << std::endl;
    if(current_state == PlayerState::RunningLeft)
        std::cout << "State : RunningLeft" << std::endl;
    if(current_state == PlayerState::RunningRight)
        std::cout << "State : RunningRight" << std::endl;
    if(current_state == PlayerState::Standing)
        std::cout << "State : Standing" << std::endl;
}

void PlayerPhysicsComponent::update(GameObject &obj, World &world)
{
    apply_map_collision(obj, world);
    set_state();

    //print_state(); // DEBUG

    do_movement(obj);

    if(current_state == PlayerState::Jumping)
        do_jumping(obj);

    if(current_state == PlayerState::Falling)
        apply_gravity(obj, world);
}

void PlayerPhysicsComponent::set_state()
{
    if(input::is_left())
        if(!is_falling_or_jumping())
            current_state = PlayerState::RunningLeft;

    if(input::is_right())
        if(!is_falling_or_jumping())
            current_state = PlayerState::RunningRight;

    if(input::is_space()) {
        PlayerState sel_state = PlayerState::Jumping;
        // Apply new states only, discard if same states.
        if(!check_state(sel_state) && !is_falling) {
            current_state = PlayerState::Jumping; // Set state.
            init_jump(); // Init variables for the new state.
        }
    }
}

bool PlayerPhysicsComponent::check_state(PlayerState new_state)
{
    // Return false when current_state doesnt equal new_state.
    // So we dont reset a jump in middle of jump.
    if(current_state != new_state)
        return false;

    return true;
}

bool PlayerPhysicsComponent::is_falling_or_jumping()
{
    if(current_state == PlayerState::Falling || current_state == PlayerState::Jumping)
        return true;
    return false;
}

void PlayerPhysicsComponent::init_fall()
{
    is_falling = true;
    multiplier_gravity = 0;
    fall_speed = 0;
}

void PlayerPhysicsComponent::init_jump()
{
    is_falling = false;
    multiplier_gravity = 8;
    fall_speed = -36;
}

void PlayerPhysicsComponent::apply_gravity(GameObject &obj, World &world)
{
    apply_fall_collision(obj, world);

    sf::Vector2f pos{ obj.get_position() };

    if(!is_falling) {
        current_state = PlayerState::Standing;
        obj.set_position(sf::Vector2f(pos.x, height));
        return;
    }

    pos.y += fall_speed;
    height = pos.y;

    obj.set_position(pos);

    fall_speed++;
}

void PlayerPhysicsComponent::apply_fall_collision(GameObject &obj, World &world)
{
    sf::FloatRect plr_rect{ obj.get_position(), obj.get_size() };

    for(auto i = 0; i < world.get_map()->get_objects().size(); i++) {
        // Player collides with a map object.
        if(plr_rect.intersects(world.get_rect(i))) {
            height = world.get_rect(i).top - obj.get_size().y; // Current height, optimization(loop only when needed).
            is_falling = false;

            std::cout << "height : " << height << std::endl;
        }
    }
}

void PlayerPhysicsComponent::apply_map_collision(GameObject &obj, World &world)
{
    sf::FloatRect plr_rect{ obj.get_position(), obj.get_size() };

    for(auto mobj : world.get_map()->get_objects())
        if(plr_rect.intersects(mobj.get_frect())) {
            if(current_state == PlayerState::RunningRight) {
                sf::Vector2f pos{ obj.get_position() };
            }
        }
}

void PlayerPhysicsComponent::do_jumping(GameObject &obj)
{
    if(multiplier_gravity <= 0) {
        current_state = PlayerState::Falling;
        init_fall();
        return;
    }

    sf::Vector2f pos{ obj.get_position() };
    pos.y += fall_speed;
    height = pos.y;

    std::cout << "Height : " << height << std::endl;

    obj.set_position(pos);

    fall_speed += multiplier_gravity;
    multiplier_gravity--;
}

void PlayerPhysicsComponent::do_movement(GameObject &obj)
{
    //sf::Clock &cl{ input->get_timer() };
    if(input::is_right()) {
        sf::Vector2f old{ obj.get_position() };
        old.x += WALK_ACCELERATION;
        obj.set_position(old);
    }

    if(input::is_left()) {
        sf::Vector2f old{ obj.get_position() };
        old.x -= WALK_ACCELERATION;

        obj.set_position(old);
    }

    if(is_falling_or_jumping()) {
        sf::Vector2f pos{ obj.get_position() };

        if(input::is_left()) {

        }

        if(input::is_right()) {

        }
    }
}
