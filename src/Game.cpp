#include "Game.h"
#include "MapObject.h"

// Player components.
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerGraphicsComponent.h"

#include "Droppin.h"

#include <iostream>

namespace Proto {

Game::Game(boost::program_options::variables_map vars)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel  = 8;

    window.create(sf::VideoMode(800, 600), "Prototype", sf::Style::Default, settings);

    parse_cmd(vars); // Parse command line options.

    window.setFramerateLimit(framelimit);

    viewport.setSize(sf::Vector2f(800, 600));
    window.setView(viewport); //! Does this need activation always when updated?

    level_info.select_map(Level::Maps::Proto);

    reset_game(); // Reset the Player and World.
}

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

void Game::editor_input(sf::Event &event)
{
    editor_rotate_obj(event);

    // Manage MapObject's (event)type; Depending on the Event what is created.
    if(edit_draw) {
        // Shift + E = Event Object => Type and ID must be set manually.
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            event_object = true;
    }

    // Assign the start position. If obj.draw is false, its the first button press.
    // Second button press will determine size of the rectangle.
    if((event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Button::Left )) {
        // Start
        if(edit_draw == false) {
            sf::Vector2i mouse_pos{ sf::Mouse::getPosition(window) };
            sf::Vector2f world_pos = window.mapPixelToCoords(mouse_pos);

            temp_obj.set_position(world_pos);
            temp_obj.set_size(sf::Vector2f());

            edit_draw = true;

            std::cout << "world_pos : (" << world_pos.x << ", "
                << world_pos.y << ")" <<  std::endl;

        } else {
            // Some debug msg
            std::cout << "mouse sz : (" << edit_mouse.x << ", "
                << edit_mouse.y << ")" << std::endl;
            std::cout << "temp_obj sz : (" << temp_obj.get_size().x << ", "
                << temp_obj.get_size().y << ")" << std::endl;

            temp_obj.set_color(sf::Color::White);
            editor_add_obj(); // Adds the object into containers.

            edit_draw = false;
            event_object = false;
        }
    }

    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
        editor_reset_temp();

    if(event.type == sf::Event::MouseMoved) {
        //edit_mouse { static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
        sf::Vector2i mouse_pos{ sf::Mouse::getPosition(window) };
        sf::Vector2f world_pos{ window.mapPixelToCoords(mouse_pos) };

        edit_mouse = world_pos;
    }

    // Save & Load map in runtime.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        world->save_map();
        world->save_events();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        world->reload_map();
}

void Game::handle_input(sf::Event &event)
{
    if(event.type == sf::Event::Closed)
        window.close();

    // This is just my personal preference.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    if(editor == true) {
        editor_input(event);
        //return;
    }

    // Reset the player position.
    if(event.type == sf::Event::KeyReleased)
        if(event.key.code == sf::Keyboard::F1)
            reset_player();

    player->handle_input(event);
    world->get_droppin()->handle_input(event);
}

///! Update the game logic.
void Game::update(sf::Time time)
{
    // Update editable_obj.shape size.
    if(edit_draw)
        temp_obj.set_size(edit_mouse - temp_obj.get_position());
    // Update the color for eventobject.
    if(event_object)
        temp_obj.set_color(sf::Color::Red);

    player->update(*world);

    world->update();
}

///! Draw the game.
void Game::draw()
{
    window.clear();

    if(edit_draw == true)
        window.draw(temp_obj);

    window.draw(deco);
    window.draw(*player);
    world->draw(window);

    window.display();
}

std::unique_ptr<Proto::GameObject> Game::create_player()
{
    Proto::PlayerInputComponent *input{ new Proto::PlayerInputComponent };
    Proto::PlayerPhysicsComponent *physics{ new Proto::PlayerPhysicsComponent{ input } };
    Proto::PlayerGraphicsComponent *graphics{ new Proto::PlayerGraphicsComponent{ viewport } };

    return std::unique_ptr<Proto::GameObject>{ 
        new Proto::GameObject{ input, physics, graphics } };
}

void Game::parse_cmd(boost::program_options::variables_map &vars)
{
    // We'll get edit mode and maps out of command line, lets parse.

    // Edit mode.
    if(vars.count("edit"))
        editor = vars["edit"].as<bool>();

    // Framelimit.
    if (vars.count("fps"))
        framelimit = vars["fps"].as<int>();

    // TODO Used only in development to jump through different levels..
    // TODO Also now when there's no way interface to change the level.

    // Select map. 
    if(vars.count("map")) {
        level_info.select_map(vars["map"].as<std::string>());
        std::cout << vars["map"].as<std::string>() << std::endl;
    }

    //std::cout << "Map : " << level_info.get_current_map_str() << std::endl;
    std::cout << "Edit : " << editor << std::endl;
    std::cout << "Fps : " << framelimit << std::endl;
}

void Game::reset_game()
{
	player = create_player();

	// Currently the initial position of the player.
    player->set_position(sf::Vector2f(200, 200));
    player->set_size(sf::Vector2f(25, 50));

    // Create world.
    world = level_info.get_world();
}

void Game::reset_player()
{
	// Reset the players position.
    player->set_position(sf::Vector2f(150, 225));
    // Annoying glitch when player is falling too fast, it falls straight through the map object...
    static_cast<PlayerPhysicsComponent*>(player->get_physics())->reset();
}

void Game::editor_add_obj()
{
    if(event_object)
        world->add_event_object(EventObject(temp_obj));
    else
        world->add_map_object(temp_obj);
}

void Game::editor_reset_temp()
{
    edit_draw = false;
    event_object = false;


}

void Game::editor_rotate_obj(sf::Event &event)
{
    if(edit_draw) {
        if(event.type == sf::Event::MouseWheelMoved) {
            auto data = static_cast<float>(event.mouseWheel.delta);

            temp_obj.set_rotation(temp_obj.get_rotation()  + data);
        }
    }
}

}
