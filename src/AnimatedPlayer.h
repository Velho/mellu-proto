#ifndef PROTO_ANIMATEDPLAYER_H
#define PROTO_ANIMATEDPLAYER_H

#include <map>
#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

namespace Proto {

class GameObject;
class Animation;
class World;

class PlayerPhysicsComponent;
class PlayerGraphicsComponent;

enum class PlayerState;

/*!
 * TODO
 * This is hardcoded bs so when u got the time,
 * revamp the animation system to be flexible and
 * support many different GameObject's, maybe polymorphism?
 */
class AnimatedPlayer : public sf::Drawable {
public:
    AnimatedPlayer(sf::View&);
    ~AnimatedPlayer();

    void handle_input(sf::Event&);
    void update(World*);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    GameObject *get_object() { return player.get(); }

private:
    std::unique_ptr<GameObject> player;
    Animation *current_anim;
    PlayerPhysicsComponent *physics;
    PlayerGraphicsComponent *graphics;

    PlayerState last_state;
    PlayerState last_running;

    int fps_counter;
    int current_frame;

    std::map<PlayerState, std::unique_ptr<Animation>> animations;

    void set_standing();
    void init_animations();

    void set_new_anim();

    std::unique_ptr<Animation> anim_idle_left();
    std::unique_ptr<Animation> anim_idle_right();

    std::unique_ptr<Animation> anim_run_left();
    std::unique_ptr<Animation> anim_run_right();

    std::unique_ptr<Animation> anim_falling();
    std::unique_ptr<Animation> anim_jumping_right();
    std::unique_ptr<Animation> anim_jumping_left();
};

}

#endif

