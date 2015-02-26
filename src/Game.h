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

// Let's get some command line options.
#include <boost/program_options.hpp>

namespace Proto {

class Game {
public:
    Game(boost::program_options::variables_map vars) :
        window{ sf::VideoMode{ 800, 600 }, "Prototype" },
        player{ create_player() } //, world{ level_info }
    {
        parse_cmd(vars); // Parse command line options.

        window.setFramerateLimit(60);

        player->set_position(sf::Vector2f(200, 200));
        player->set_size(sf::Vector2f(25, 50));

        viewport.setSize(sf::Vector2f(800, 600));
        window.setView(viewport); //! Does this need activation always when updated?

        // Create world after the world has been created.
        world = std::unique_ptr<World>(new World(level_info));
    }

    int run();

private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::View viewport;

    std::unique_ptr<GameObject> player;

    Droppin drop_mech;
    Events::EventType evt_type;

    ///< Window size.
    const int WIN_WIDTH{ 800 };
    const int WIN_HEIGHT{ 600 };

    Level level_info; ///< Keeps current level.
    std::unique_ptr<World> world; ///< World object => Draws maps & events according to Level.

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

    void editor_add_map_obj(); ///< Adds map object into *map.
    void editor_create_platform(); ///< Creates event object out of MapObject.

    void parse_cmd(boost::program_options::variables_map&);
};

}

#endif
