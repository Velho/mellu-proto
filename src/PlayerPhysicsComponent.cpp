#include "PlayerPhysicsComponent.h"
#include "World.h"

using Proto::PlayerPhysicsComponent;
using Proto::GameObject;
using Proto::World;

using input = Proto::PlayerInputComponent;

///< TODO Implement move_ground() & move_air()

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

void PlayerPhysicsComponent::reset()
{
	init_fall();
}

void PlayerPhysicsComponent::print_state()
{
    static PlayerState last_state = PlayerState::Standing;

    if (!check_state(last_state)) {
        if (current_state == PlayerState::Falling)
            std::cout << "State : Falling" << std::endl;
        if (current_state == PlayerState::Jumping)
            std::cout << "State : Jumping" << std::endl;
        if (current_state == PlayerState::RunningLeft)
            std::cout << "State : RunningLeft" << std::endl;
        if (current_state == PlayerState::RunningRight)
            std::cout << "State : RunningRight" << std::endl;
        if (current_state == PlayerState::Standing)
            std::cout << "State : Standing" << std::endl;

        std::cout << "Velocity : " << velocity.x << std::endl;
    }
    last_state = current_state;
}

void PlayerPhysicsComponent::update(GameObject &obj, World &world)
{
    set_state();
    add_velocity();

    print_state(); // DEBUG

    if(current_state == PlayerState::Jumping)
        do_jumping(obj);

    if(current_state == PlayerState::Falling)
        apply_gravity(obj, world);

    apply_map_collision(obj, world);
    evt_mgr.update(obj, world);

    // We can move in every PlayerState.
    do_movement(obj);
}

void PlayerPhysicsComponent::set_state()
{
    // State changing for movement should be moved into do_movement(..) method.
    if(input_cmp->current_keypress == input::KeyPress::Left)
        if(!is_falling_or_jumping()) {
            current_state = PlayerState::RunningLeft;
        }

    if (input_cmp->current_keypress == input::KeyPress::Right)
        if(!is_falling_or_jumping()) {
            current_state = PlayerState::RunningRight;
        }

    if(input::is_space()) {
        PlayerState sel_state = PlayerState::Jumping;
        // Apply new states only, discard if same states.
        if(!check_state(sel_state) && current_state != PlayerState::Falling) {
            current_state = PlayerState::Jumping; // Set state.
            init_jump(); // Init variables for the new state.
        }
    }

    /* TODO If new key is pressed while old key is pressed, after releasing the old
     * key current_keypress get's set to None which resets the velocity. FIX */
    if (input_cmp->current_keypress == input::KeyPress::None && !is_falling_or_jumping()) {
        current_state = PlayerState::Standing;
        velocity.x = 0;
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
        //evt_mgr.evt_obj = nullptr;
        evt_mgr.evt_coll = false;
    }
}

void PlayerPhysicsComponent::init_jump()
{
    is_falling = false;
    multiplier_gravity = 8;
    jump_speed = -36;

    velocity.x = 0;
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

    int idx{ 0 };
    //for(auto i = 0; i < world.get_map()->get_objects().size(); i++) {
    for(auto &mobj : world.get_map_objects()) {

        // Rect for map objects surface. Calculating collision on surface when falling is more relevant. Surface is 2px high.
        sf::FloatRect mobj_rekt{ mobj->get_frect().left, mobj->get_frect().top, mobj->get_frect().width, 2 };

        // Player collides with a map object.
        // if(plr_rect.intersects(world.get_rect(i)) && is_falling) {
        if(plr_rect.intersects(mobj_rekt) && is_falling) {
            height = mobj->get_frect().top - obj.get_size().y; // Current height, optimization(loop only when needed).
            is_falling = false;
            fall_obj = mobj.get();

            std::cout << "height at idx(" << idx << ") : " << height << std::endl;
        }

        idx++;
    }
}

void PlayerPhysicsComponent::apply_map_collision(GameObject &obj, World &world)
{
    sf::FloatRect plr_rect{ sf::Vector2f(obj.get_position().x - WALK_ACCELERATION + 1, obj.get_position().y),
        sf::Vector2f(obj.get_size().x + WALK_ACCELERATION + 1, obj.get_size().y) };

    /*
     * TODO There's small bug in the collision calculation when player hits
     * the ground, collision is detected and taken back to the opposite direction
     * by amount WALK_ACCELERATION.
     *
     * Collision to right and left should be calculated from the most edge point
     * from each side, not whole collision rectangle.
     */
    if (current_state != PlayerState::Standing) {
        for (auto &mobj : world.get_map_objects()) {
            if (current_state == PlayerState::RunningRight) {
                sf::Vector2f right{ obj.get_position().x + WALK_ACCELERATION, obj.get_position().y + obj.get_size().y - 1 };
                if (mobj->get_frect().contains(right))
                    velocity.x = 0;
            }

            if (current_state == PlayerState::RunningLeft) {
                //sf::FloatRect left{ sf::Vector2f(obj.get_position().x - WALK_ACCELERATION, obj.get_position().y), sf::Vector2f(1, 1) };
                //if (obj.get_rect().intersects(left))
                    //velocity.x = 0;
                sf::Vector2f left{ obj.get_position().x - WALK_ACCELERATION, obj.get_position().y + obj.get_size().y - 1 };

                if (mobj->get_frect().contains(left))
                    velocity.x = 0;
            }
        /*
         ______  _
        |      ||x|__   -> This is how its currently done, by calculating against whole collision box.
        |______|_____|

         ______
        |      ||x|__   -> This is how it should be done, by calculating against points on x axis.
        |______|_____|
       */
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


    if(current_state != PlayerState::Jumping) {
        // Calculate the collision from one pixel on the surface.
        sf::FloatRect plr_rect{ obj.get_position(),
                    sf::Vector2f(obj.get_size().x, obj.get_size().y + 1) };

        if(fall_obj != nullptr) {
            // If collided map object doesnt contain gameobject position => We are falling.
            if(!fall_obj->get_frect().intersects(plr_rect) &&
                    current_state != PlayerState::Falling) {
                current_state = PlayerState::Falling;
                init_fall();
                std::cout << "fall_obj() => MapObject" << std::endl;
            }
        }

        // Apply fall for EventObject.
        if(evt_mgr.evt_obj != nullptr && evt_mgr.evt_coll != false) {
            if(!evt_mgr.evt_obj->get_rect().intersects(plr_rect) &&
                    current_state != PlayerState::Falling) {
                current_state = PlayerState::Falling;
                init_fall();
                std::cout << "fall_obj() => EvtObject" << std::endl;
            }
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
    obj.set_position(obj.get_position() + velocity);
}

void PlayerPhysicsComponent::add_velocity()
{
    if (input_cmp->current_keypress == input::KeyPress::Right) {
        velocity.x = WALK_ACCELERATION;
    }
    if (input_cmp->current_keypress == input::KeyPress::Left) {
        velocity.x = -WALK_ACCELERATION;
    }
}
