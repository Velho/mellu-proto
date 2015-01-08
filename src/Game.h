#ifndef PROTO_GAME_H
#define PROTO_GAME_H

#include <SFML/Graphics.hpp>

namespace Proto {

class Game {
public:
    Game() :
        window{ sf::VideoMode{ 600, 400 }, "Prototype" }
    {
        window.setFramerateLimit(60);
    }

    int run();

private:
    //std::string wintitle{ "Proto" + winversion };
    //std::string winversion{ "v0.1" };

    sf::RenderWindow window;
    sf::Clock clock;

    void handle_input(sf::Event);
    void update(sf::Time);
    void draw();
};

}

#endif
