#include "Game.h"
#include "MapObject.h"

// Player components.
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerGraphicsComponent.h"

#include "Droppin.h"

#include "World.h"
#include "Renderer.h"

#include "Decoration.h"

#include "EditInput.h"
#include "EditText.h"

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

    /*
    input_edit = std::unique_ptr<EditInput>(new EditInput);
    input_edit->set_position(sf::Vector2f(20, 20));
    input_edit->set_active(true);
    */

    if(editor)
        editor_init();
}

Game::~Game()
{
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

    // get some input.
    //input_edit->handle_input(event);


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
            show_edit_texts = true;
        else
            show_edit_texts = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
        if(!fill_layout) {
            fill_layout = true;
            active_input = 0;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
        if(!fill_deco) {
            fill_deco = true;
            deco_input = 0;
        }
    }

    for(auto &t : vec_inputs)
        t->handle_input(event);
    for(auto &t : deco_inputs)
        t->handle_input(event);
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

    editor_renderer_update_text();
    editor_renderer_update_lay_inputs();
    editor_renderer_update_deco_inputs();
}

///! Draw the game.
void Game::draw()
{
    window.clear();

    if(edit_draw == true)
        window.draw(temp_obj);

    window.draw(*player);
    world->draw(window);

    //input_edit->draw(window);
    editor_renderer_draw_text();

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

    // Initialize renderer.
    renderer = std::unique_ptr<Renderer>(new Renderer(level_info, world.get()));
}

void Game::reset_player()
{
	// Reset the players position.
    player->set_position(sf::Vector2f(150, 225));
    // Annoying glitch when player is falling too fast, it falls straight through the map object...
    static_cast<PlayerPhysicsComponent*>(player->get_physics())->reset();
}

void Game::editor_init()
{
    editor_renderer_init_obj_info();
    editor_renderer_init_inputs();
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

void Game::editor_renderer_add_layout()
{
    std::cout << "Input done, adding layout to renderer." << std::endl;

    renderer->add_layout(temp_lay);
}

void Game::editor_renderer_add_decoration()
{
    std::cout << "Input done, adding decoration to renderer." << std::endl;

    renderer->add_decoration(Decoration(0, temp_deco_pos));
}

void Game::editor_renderer_init_obj_info()
{
    // Add MapObjects information.
    for(auto &m_obj : world->get_map_objects()) {
        std::string m_id_str("M{" + std::to_string(static_cast<int>(RenderType::Map)) + "} : " + std::to_string(m_obj->get_id()));

        // Print map id's.
        vec_texts.emplace_back(std::unique_ptr<EditText>(
            new EditText(m_obj->get_position(), m_id_str)));
    }

    // Add EventObjects information.
    for(auto &e_obj : world->get_evt_objects()) {
        std::string e_id_str("E{" + std::to_string(static_cast<int>(RenderType::Event)) + "} : " + std::to_string(e_obj->get_evt_id()));

        vec_texts.emplace_back(std::unique_ptr<EditText>(
                new EditText(e_obj->get_position(), e_id_str)));
    }
}

void Game::editor_renderer_init_inputs()
{
    // References to required variables..
    // Lambda's fakap scope shit crap
    auto &stoi = p_stoi;
    // Layout specific
    Layout &ref_temp = temp_lay;
    int &current = active_input;
    // Decoration specific
    sf::Vector2f &ref_deco = temp_deco_pos;
    int &deco_inp = deco_input;

    // Layout inputs.
    vec_inputs.emplace_back(std::unique_ptr<EditInput>(
            new EditInput(sf::Vector2f(50, 50),
                [&ref_temp, &current, &stoi](std::string r) { // Id
                    int id{ 0 };

                    if(stoi(r, id)) {
                        ref_temp = Layout(0, id);
                        current++; // If exception is caught, dont proceed.
                    } else
                        std::cout << "Invalid argument!" << std::endl;
                }
    )));

    vec_inputs.emplace_back(std::unique_ptr<EditInput>(
            new EditInput(sf::Vector2f(50, 50),
                [&ref_temp, &current, &stoi](std::string r) { // Type
                    int type{ 0 };

                    if(stoi(r, type)) {
                        ref_temp = Layout(0,
                                ref_temp.get_obj_id(),
                                static_cast<RenderType>(std::stoi(r)));
                        current++;
                    } else
                        std::cout << "Invalid argument!" << std::endl;
                }
    )));


    vec_inputs.emplace_back(std::unique_ptr<EditInput>(
            new EditInput(sf::Vector2f(50, 50),
                [&ref_temp, &current, &stoi](std::string r) { // Texture
                    int tex{ 0 };

                    if(stoi(r, tex)) {
                        ref_temp = Layout(0,
                                ref_temp.get_obj_id(),
                                ref_temp.get_render_type(),
                                static_cast<Textures>(std::stoi(r)));
                        current++;
                    } else
                        std::cout << "Invalid argument!" << std::endl;
                }
    )));

    vec_inputs.emplace_back(std::unique_ptr<EditInput>(
            new EditInput(sf::Vector2f(50, 50),
                [&ref_temp, &current, &stoi](std::string r) { // Priority
                    int prio{ 0 };

                    if(stoi(r, prio)) {
                        ref_temp = Layout(0,
                                ref_temp.get_obj_id(),
                                ref_temp.get_render_type(),
                                ref_temp.get_texture(),
                                static_cast<int>(std::stoi(r)));
                        current++;
                    } else
                        std::cout << "Invalid argument!" << std::endl;
                }
    )));

    deco_inputs.emplace_back(std::unique_ptr<EditInput>(
            new EditInput(sf::Vector2f(50, 50),
                    [&ref_deco, &deco_inp, &stoi](std::string r) { // Retrieve X
                        int x{ 0 };

                        if(stoi(r, x)) {
                            ref_deco.x = x;
                            deco_inp++;
                        } else
                            std::cout << "Invalid argument!" << std::endl;
                    }
    )));

    deco_inputs.emplace_back(std::unique_ptr<EditInput>(
            new EditInput(sf::Vector2f(50, 50),
                    [&ref_deco, &deco_inp, &stoi](std::string r) { // Retrieve Y.
                        int y{ 0 };

                        if(stoi(r, y)) {
                            ref_deco.y = y;
                            deco_inp++;
                        } else
                            std::cout << "Invalid argument!" << std::endl;
                    }
    )));

}

static int lay_last_run = -1;

void Game::editor_renderer_update_lay_inputs()
{
    // Return, if fill_layout false.
    if(!fill_layout)
        return;

    // Print on standard output what to input.
    if(active_input != lay_last_run) {
        if(active_input == 0) // Id
            std::cout << "Input : Object Id" << std::endl;
        if(active_input == 1) // Type
            std::cout << "Input : Object Type" << std::endl;
        if(active_input == 2) // Texture
            std::cout << "Input : Texture" << std::endl;
        if(active_input == 3) // Priority
            std::cout << "Input : Priority" << std::endl;
    }

    // It seems we are complete.
    if(active_input == 4) {
        fill_layout = false;
        active_input = -1;

        // Add complete Layout to renderer.
        editor_renderer_add_layout();
    }

    // Update only the active input.
    if(active_input != -1)
        vec_inputs[active_input]->update();

    // Activate correct input.
    int idx{ 0 };
    for(auto &i : vec_inputs) {
        if(idx == active_input) {
            i->set_active(true);
        }
        else
            i->set_active(false);

        idx++;
    }

    lay_last_run = active_input;
}

static int deco_last_run = -1;

void Game::editor_renderer_update_deco_inputs()
{
    // Misleading stuff..
    // deco_input is the counter for active input.
    // deco_inputs is the container for inputs.

    if(!fill_deco)
        return;

    // Print on standard output what to input.
    if(deco_input != deco_last_run) {
        if(deco_input == 0) // Id
            std::cout << "Input : X" << std::endl;
        if(deco_input == 1) // Type
            std::cout << "Input : Y" << std::endl;
    }

    if(deco_input == 2) {
        fill_deco = false;
        deco_input = -1;

        editor_renderer_add_decoration();
    }

    if(deco_input != -1)
        deco_inputs[deco_input]->update();

    int idx{ 0 };
    for(auto &i : deco_inputs) {
        if(idx == deco_input)
            i->set_active(true);
        else
            i->set_active(false);

        idx++;
    }

    deco_last_run = deco_input;
}

void Game::editor_renderer_update_text()
{
    for(auto &t : vec_texts) {
        if(show_edit_texts)
            t->set_show(true);
        else
            t->set_show(false);

        t->update();
    }
}

void Game::editor_renderer_draw_text()
{
    if(fill_layout)
        for(auto &t : vec_inputs)
            if(t->is_active())
                t->draw(window);

    if(!show_edit_texts)
        return;

    for(auto &t : vec_texts)
        t->draw(window);
}

}
