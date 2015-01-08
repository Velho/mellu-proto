#include "Game.h"

using Proto::Game;

int Game::run()
{
    // Game logic & draw loop.
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event))
            handle_input(event);

        sf::Time elapsed = clock.restart();

        update(elapsed);
        draw();
    }

    return 0;
}

void Game::handle_input(sf::Event event)
{
    if(event.type == sf::Event::Closed)
        window.close();

    // This is just my personal preference.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

///! Update the game logic.
void Game::update(sf::Time time)
{

}

///! Draw the game.
void Game::draw()
{
    window.clear();

    window.display();
}
