#include "PlayerPhysicsComponent.h"

using Proto::PlayerPhysicsComponent;
using Proto::GameObject;
using Proto::World;

using input = Proto::PlayerInputComponent;

/*
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
*/

void PlayerPhysicsComponent::print_state()
{
    std::cout << "is_falling : " << is_falling << std::endl;
}

void PlayerPhysicsComponent::update(GameObject &obj, World &world)
{
    set_state();

    //print_state(); // DEBUG

    // We can move in every PlayerState.
    do_movement(obj);

    if(current_state == PlayerState::Jumping)
        do_jumping(obj);

    if(current_state == PlayerState::Falling)
        apply_gravity(obj, world);

    apply_map_collision(obj, world);
}

void PlayerPhysicsComponent::set_state()
{
    // State changing for movement should be moved into do_movement(..) method.
    if(input::is_left())
        if(!is_falling_or_jumping()) {
            current_state = PlayerState::RunningLeft;
            last_keypress = Keypress::Left;
        }

    if(input::is_right())
        if(!is_falling_or_jumping()) {
            current_state = PlayerState::RunningRight;
            last_keypress = Keypress::Right;
        }

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
    if(current_state == PlayerState::Falling ||
            current_state == PlayerState::Jumping)
        return true;
    return false;
}

void PlayerPhysicsComponent::init_fall()
{
    // We must be sure not to reset fall variables while falling.. Retard check.
    // I think this cannot occur anymore though but lets be sure.
    if(!is_falling) {
        is_falling = true;
        fall_speed = 0;
        fall_obj = nullptr;
    }
}

void PlayerPhysicsComponent::init_jump()
{
    is_falling = false;
    multiplier_gravity = 8;
    jump_speed = -36;
}

void PlayerPhysicsComponent::apply_gravity(GameObject &obj, World &world)
{
    apply_fall_collision(obj, world);

    sf::Vector2f pos{ obj.get_position() };

    if(!is_falling) {
        current_state = PlayerState::Standing;
        obj.set_position(sf::Vector2f(pos.x, height));
        std::cout << "Player::Standing" << std::endl;
        input_cmp->last_keypress = input::KeyPress::None;
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

        // Rect for map objects surface. Calculating collision on surface when falling is more relevant. Collision for movement comes next.
        sf::FloatRect mobj_rekt{ world.get_rect(i).left, world.get_rect(i).top, world.get_rect(i).width, 5 };

        // Player collides with a map object.
        // if(plr_rect.intersects(world.get_rect(i)) && is_falling) {
        if(plr_rect.intersects(mobj_rekt) && is_falling) {
            height = world.get_rect(i).top - obj.get_size().y; // Current height, optimization(loop only when needed).
            is_falling = false;
            fall_obj = &world.get_map()->get_objects()[i];

            std::cout << "height at idx(" << i << ") : " << height << std::endl;
        }
    }
}

void PlayerPhysicsComponent::apply_map_collision(GameObject &obj, World &world)
{
    sf::FloatRect plr_rect{ obj.get_position(), sf::Vector2f(obj.get_size().x + 2, obj.get_size().y) };

    for(auto mobj : world.get_map()->get_objects()) {
        if(plr_rect.intersects(mobj.get_frect())) {
            sf::Vector2f pos{ obj.get_position() };

            // If player tries to walk into wall, take a step back(=> Makes a boing away from the wall).
            if(current_state == PlayerState::RunningRight || input_cmp->last_keypress == input::KeyPress::Right) {
                pos.x -= WALK_ACCELERATION;
                obj.set_position(pos);
            }
            if(current_state == PlayerState::RunningLeft || input_cmp->last_keypress == input::KeyPress::Left) {
                pos.x += WALK_ACCELERATION;
                obj.set_position(pos);
            }
        }
    }

   /*
    * Try if the fall from map object can be calculated from comparing
    * gameobjects x, y positions with game objects size. This needs some optimization,
    * wrong code gets repeated after and after trying accomplish different things.
    * It doesnt match up because of the height variable. This needs some rework!
    *
    * On Windows height variable causes some nasty bugs where apply_gravity(..)
    * method's first [if] clause bursts in while falling when player moves to intersect
    * with fall_obj.
    */

    /*
     */

        // Make sure that fall object is not null pointer(aka no collision happened yet).
        // Or that we are in the middle of jump.


    if(fall_obj != nullptr && current_state != PlayerState::Jumping) {
        sf::Vector2f plr_coll_pos(obj.get_position().x + obj.get_size().x, obj.get_position().y + obj.get_size().y);
        //sf::FloatRect plr_coll_rect(obj.get_position(), obj.get_size());

        // If collided map object doesnt contain gameobject position => We are falling.
        if(!fall_obj->get_frect().contains(plr_coll_pos) && current_state != PlayerState::Falling) {
            current_state = PlayerState::Falling;
            init_fall();
            std::cout << "fall_obj()" << std::endl;
        }
    }
}

void PlayerPhysicsComponent::do_jumping(GameObject &obj)
{
    /**
     * jump speed is calculated:
     * while(multiplier_gravity > 0) {
     *  amount += multiplier_gravity;
     *  multiplier_gravity--;
     * }
     */

    if(multiplier_gravity <= 0) {
        current_state = PlayerState::Falling;
        init_fall();
        return;
    }

    sf::Vector2f pos{ obj.get_position() };
    pos.y += jump_speed;
    height = pos.y;

    obj.set_position(pos);

    jump_speed += multiplier_gravity;
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
