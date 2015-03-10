#ifndef PROTO_GAME_H
#define PROTO_GAME_H

#include <SFML/Graphics.hpp>

#include "GameObject.h"

// Player components.
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerGraphicsComponent.h"

#include "Droppin.h"
#include "World.h"

#include "MapObject.h"
// Let's get some command line options.
#include <boost/program_options.hpp>

namespace Proto {

class Game {
public:
    Game(boost::program_options::variables_map);

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

    Level level_info; ///< Keeps current level.
    std::unique_ptr<World> world; ///< World object => Draws maps & events according to Level.

    ///! Used as temporary object for Map editing.
    MapObject temp_obj;
    sf::Vector2f edit_mouse;
    bool edit_draw{ false };
    bool event_object{ false };

    bool editor{ false };

    ///< Creates a player GameObject.
    std::unique_ptr<GameObject> create_player();

    void editor_input(sf::Event&); ///< Editing maps.
    void handle_input(sf::Event&);
    void update(sf::Time);
    void draw();

    void editor_add_obj(); ///< Adds map object into *map.
    void editor_create_platform(); ///< Creates event object out of MapObject.

    void parse_cmd(boost::program_options::variables_map&);
};

}

#endif
