#include "Game.h"
#include "MapObject.h"

#include <iostream>

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

void Game::editor_input(sf::Event event)
{
    // Assign the start position. If obj.draw is false, its the first button press.
    // Second button press will determine size of the rectangle.
    if((event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left )) {
        // Start
        if(edit_draw == false) {
            sf::Vector2f mouse = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            temp_obj.setPosition(mouse);
            temp_obj.setSize(sf::Vector2f());

            edit_draw = true;
            std::cout << "(" << mouse.x << ", " << mouse.y << ")" <<  std::endl;

        } else {
            map.addObject(Proto::MapObject(temp_obj));
            edit_draw = false;
        }
    }

    if(event.type == sf::Event::MouseMoved)
        edit_mouse = { static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
}

void Game::handle_input(sf::Event event)
{
    if(event.type == sf::Event::Closed)
        window.close();

    // This is just my personal preference.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    if(editor == true)
        editor_input(event);
}

///! Update the game logic.
void Game::update(sf::Time time)
{
    // Update editable_obj.shape size.
    if(edit_draw == true) {
        temp_obj.setSize(edit_mouse - temp_obj.getPosition());
    }
}

///! Draw the game.
void Game::draw()
{
    window.clear();

    if(edit_draw == true)
        window.draw(temp_obj);

    map.draw(window);
    window.display();
}
