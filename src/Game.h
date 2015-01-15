#ifndef PROTO_GAME_H
#define PROTO_GAME_H

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "World.h"

// Player components.
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerGraphicsComponent.h"


namespace Proto {

class Game {
public:
    Game(bool edit) :
        window{ sf::VideoMode{ 800, 600 }, "Prototype" },
        editor{ edit }, map{ world.getMap() },
        player{ new PlayerInputComponent(),
                new PlayerPhysicsComponent(clock),
                new PlayerGraphicsComponent(viewport)}
    {
        window.setFramerateLimit(60);

        player.setPosition(sf::Vector2f(200, 200));
        player.setSize(sf::Vector2f(50, 75));

        viewport.setSize(sf::Vector2f(800, 600));
        window.setView(viewport); //! Does this need activation always when updated?
    }

    int run();

private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::View viewport;

    GameObject player;

    const int WIN_WIDTH{ 800 };
    const int WIN_HEIGHT{ 600 };

    World world;
    Map *map;
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
