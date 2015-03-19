#include "Game.h"
#include "MapObject.h"

#include <iostream>

namespace Proto {

Game::Game(boost::program_options::variables_map vars) :
    window{ sf::VideoMode{ 800, 600 }, "Prototype" },
    player{ create_player() } //, world{ level_info }
{
    parse_cmd(vars); // Parse command line options.

    window.setFramerateLimit(60);

    player->set_position(sf::Vector2f(200, 200));
    player->set_size(sf::Vector2f(25, 50));

    viewport.setSize(sf::Vector2f(800, 600));
    window.setView(viewport); //! Does this need activation always when updated?

    level_info.select_map(Level::Maps::Proto);
    // Create world after the world has been created(hmm..?).
    world = level_info.get_world();
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
            //event_object = false;

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

    player->handle_input(event);
    //drop_mech.handle_input(event);
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
    //drop_mech.update(world);
    world->update();
}

///! Draw the game.
void Game::draw()
{
    window.clear();

    if(edit_draw == true)
        window.draw(temp_obj);

    player->draw(window);
    //drop_mech.draw(window);
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

    // TODO Used only in development to jump through different levels..
    // TODO Also now when there's no way interface to change the level.

    // Select map. 
    if(vars.count("map")) {
        level_info.select_map(vars["map"].as<std::string>());
        std::cout << vars["map"].as<std::string>() << std::endl;
    }

    //std::cout << "Map : " << level_info.get_current_map_str() << std::endl;
    std::cout << "Edit : " << editor << std::endl;
}

void Game::editor_add_obj()
{
    if(event_object)
        world->add_event_object(EventObject(temp_obj));
    else
        world->add_map_object(temp_obj);
}
}
