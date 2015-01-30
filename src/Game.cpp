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
            temp_obj.set_position(mouse);
            temp_obj.set_size(sf::Vector2f());

            edit_draw = true;
            std::cout << "pos : (" << mouse.x << ", " << mouse.y << ")" <<  std::endl;

        } else {
            std::cout << "mouse sz : (" << edit_mouse.x << ", " << edit_mouse.y << ")" << std::endl;
            std::cout << "temp_obj sz : (" << temp_obj.get_size().x << ", " << temp_obj.get_size().y << ")" << std::endl;
            map->add_object(Proto::MapObject(temp_obj));
            edit_draw = false;
        }
    }

    if(event.type == sf::Event::MouseMoved)
        edit_mouse = { static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };

    // CTRL + S ???
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        map->save_map();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        map->set_reload(true);
}

void Game::handle_input(sf::Event event)
{
    if(event.type == sf::Event::Closed)
        window.close();

    // This is just my personal preference.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    if(editor == true) {
        editor_input(event);
        return;
    }

    player->handle_input(event);
    drop_mech.handle_input(event);
}

///! Update the game logic.
void Game::update(sf::Time time)
{
    // Update editable_obj.shape size.
    if(edit_draw == true)
        temp_obj.set_size(edit_mouse - temp_obj.get_position());

    player->update(world);
    drop_mech.update(world);
    world.update();
}

///! Draw the game.
void Game::draw()
{
    window.clear();

    if(edit_draw == true)
        window.draw(temp_obj);

    player->draw(window);
    drop_mech.draw(window);
    world.draw(window);

    window.display();
}

std::unique_ptr<Proto::GameObject> Game::create_player()
{
    Proto::PlayerInputComponent *input{ new Proto::PlayerInputComponent };
    Proto::PlayerPhysicsComponent *physics{ new Proto::PlayerPhysicsComponent{ input } };
    Proto::PlayerGraphicsComponent *graphics{ new Proto::PlayerGraphicsComponent{ viewport } };

    return std::unique_ptr<Proto::GameObject>{ new Proto::GameObject{ input, physics, graphics } };
}
