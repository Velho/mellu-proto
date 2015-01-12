#ifndef PROTO_GAME_H
#define PROTO_GAME_H

#include <SFML/Graphics.hpp>
#include "Map.h"

namespace Proto {

class Game {
public:
    Game(bool edit) :
        window{ sf::VideoMode{ 800, 600 }, "Prototype" },
        editor{ edit }
    {
        window.setFramerateLimit(60);
    }

    int run();

private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::View viewport;

    const int WIN_WIDTH{ 800 };
    const int WIN_HEIGHT{ 600 };

    Map map;
    ///! Used as temporary object for Map editing.
    MapObject temp_obj;
    bool edit_draw{ false };
    sf::Vector2f edit_mouse;

    bool editor{ false };

    void editor_input(sf::Event); ///! Editing maps.
    void handle_input(sf::Event);
    void update(sf::Time);
    void draw();
};

}

#endif
