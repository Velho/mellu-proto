#include "AnimatedPlayer.h"

#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerGraphicsComponent.h"

#include "Animation.h"
#include "Resources.h"
#include "World.h"

namespace Proto {

AnimatedPlayer::AnimatedPlayer(sf::View &view) :
        fps_counter(0), current_frame(0), last_running(PlayerState::RunningLeft), last_state(PlayerState::Standing)
{
    auto *p_i{ new PlayerInputComponent };
    PlayerPhysicsComponent *p_p{ new PlayerPhysicsComponent(p_i) };
    PlayerGraphicsComponent *p_g{ new PlayerGraphicsComponent(view) };

    player = std::unique_ptr<GameObject>(
            new GameObject(p_i, p_p, p_g));

    // Store the pointer for later use.
    graphics = p_g;
    physics = p_p;

    init_animations();

    set_new_anim();
}

AnimatedPlayer::~AnimatedPlayer()
{

}

void AnimatedPlayer::handle_input(sf::Event &event)
{
    player->handle_input(event);
}

void AnimatedPlayer::update(World *world)
{
    if(fps_counter > current_anim->get_fps()) {
        fps_counter = 0;
        current_frame++;

        if(current_frame >= current_anim->get_framecount())
            current_frame = 0;

        //std::cout << current_frame << ", " << current_anim->get_frame(current_frame).left << ";" << current_anim->get_frame(current_frame).top << std::endl;
    }

    player->update(*world);

    // Easily determine which way orienting.
    /*
    if(physics->current_state == PlayerState::RunningLeft)
        last_running = PlayerState::RunningLeft;
    else if(physics->current_state == PlayerState::RunningRight)
        last_running = PlayerState::RunningRight;

    if(physics->current_state == PlayerState::Standing)
        if(last_running == PlayerState::RunningLeft)
            physics->current_state == PlayerState::StandingLeft;
        else if(last_running == PlayerState::RunningRight)
            physics->current_state == PlayerState::StandingRight;
*/
    //if(physics->current_state == PlayerState::StandingLeft || physics->current_state == PlayerState::StandingRight && physics->current_state == PlayerState::RunningLeft && physics->current_state == PlayerState::RunningRight)
    set_new_anim();

    fps_counter++;
    last_state = physics->current_state;
}

void AnimatedPlayer::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    static_cast<PlayerGraphicsComponent*>(
            player->get_graphics())->shape.setTextureRect(
                    current_anim->get_frame(current_frame));

    target.draw(*player);
}

void AnimatedPlayer::set_standing()
{
}

void AnimatedPlayer::init_animations()
{
    animations.insert(std::make_pair(PlayerState::Standing, anim_falling()));
    animations.insert(std::make_pair(PlayerState::StandingLeft, anim_idle_left()));
    animations.insert(std::make_pair(PlayerState::RunningLeft, anim_run_left()));
    animations.insert(std::make_pair(PlayerState::RunningRight, anim_run_right()));
    animations.insert(std::make_pair(PlayerState::StandingRight, anim_idle_right()));
    animations.insert(std::make_pair(PlayerState::Falling, anim_falling()));
    animations.insert(std::make_pair(PlayerState::Jumping, anim_jumping_left()));
}

void AnimatedPlayer::set_new_anim()
{
    if(physics->current_state != last_state) {
        current_anim = animations.at(physics->current_state).get();

        graphics->shape.setTexture(current_anim->get_texture());
        fps_counter = 14;
    }
}

std::unique_ptr<Animation> AnimatedPlayer::anim_idle_right()
{
    std::unique_ptr<Animation> anim(
            new Animation(Textures::IdleRight, 2));

    anim->insert_frame({0, 0, 406, 1024});
    anim->insert_frame({406, 0, 406, 1024});

    return anim;
}

std::unique_ptr<Animation> AnimatedPlayer::anim_idle_left()
{
    std::unique_ptr<Animation> anim(
            new Animation(Textures::IdleLeft, 2));

    anim->insert_frame({0, 0, 447, 1024});
    anim->insert_frame({447, 0, 447, 1024});

    return anim;
}

std::unique_ptr<Animation> AnimatedPlayer::anim_run_left()
{
    std::unique_ptr<Animation> anim(
        new Animation(Textures::RunLeft, 5));

    anim->insert_frame({0, 0, 230, 399});
    anim->insert_frame({230, 0, 203, 399});
    anim->insert_frame({410, 0, 203, 399});
    anim->insert_frame({615, 0, 180, 399});
    anim->insert_frame({795, 0, 229, 399});

    return anim;
}

std::unique_ptr<Animation> AnimatedPlayer::anim_run_right()
{
    std::unique_ptr<Animation> anim(
        new Animation(Textures::RunRight, 5));

    anim->insert_frame({0, 0, 230, 399});
    anim->insert_frame({230, 0, 180, 399});
    anim->insert_frame({410, 0, 203, 399});
    anim->insert_frame({615, 0, 180, 399});
    anim->insert_frame({795, 0, 229, 399});

    return anim;
}

std::unique_ptr<Animation> AnimatedPlayer::anim_falling()
{
    std::unique_ptr<Animation> anim(
            new Animation(Textures::IdleLeft, 1));

    anim->insert_frame({0, 0, 447, 1024});
 //   anim->insert_frame({447, 0, 447, 1024});

    return anim;
}

std::unique_ptr<Animation> AnimatedPlayer::anim_jumping_right()
{
    std::unique_ptr<Animation> anim(
            new Animation(Textures::HyppyOikea, 4));

    anim->insert_frame({0, 0, 447, 1024});
 //   anim->insert_frame({447, 0, 447, 1024});

    return anim;
}

std::unique_ptr<Animation> AnimatedPlayer::anim_jumping_left()
{
    std::unique_ptr<Animation> anim(
            new Animation(Textures::HyppyVasen, 4, 30));

    anim->insert_frame({0, 0, 255, 1024});
    anim->insert_frame({255, 0, 255, 1024});
    anim->insert_frame({510, 0, 225, 1024});
    anim->insert_frame({765, 0, 225, 1024});

    return anim;
}

}
