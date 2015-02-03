#ifndef PROTO_GAME_H
#define PROTO_GAME_H

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "World.h"

// Player components.
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerGraphicsComponent.h"

#include "Droppin.h"


namespace Proto {

class Game {
public:
    Game(bool edit) :
        window{ sf::VideoMode{ 800, 600 }, "Prototype" },
        editor{ edit }, map{ world.get_map() },
        player{ create_player() }
    {
        window.setFramerateLimit(60);

        player->set_position(sf::Vector2f(200, 200));
        player->set_size(sf::Vector2f(25, 50));

        viewport.setSize(sf::Vector2f(800, 600));
        window.setView(viewport); //! Does this need activation always when updated?
    }

    int run();

private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::View viewport;

    std::unique_ptr<GameObject> player;

    Droppin drop_mech;

    ///< Window size.
    const int WIN_WIDTH{ 800 };
    const int WIN_HEIGHT{ 600 };

    World world;
    Map *map;
    ///! Used as temporary object for Map editing.
    MapObject temp_obj;
    bool edit_draw{ false };
    sf::Vector2f edit_mouse;

    bool editor{ false };

    ///< Creates a player GameObject.
    std::unique_ptr<GameObject> create_player();

    void editor_input(sf::Event&); ///< Editing maps.
    void handle_input(sf::Event&);
    void update(sf::Time);
    void draw();
};

}

#endif
