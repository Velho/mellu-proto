#ifndef PROTO_GAME_H
#define PROTO_GAME_H

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "MapObject.h"
#include "Layout.h"

#include "Level.h"
#include "AnimatedPlayer.h"

// Let's get some command line options.
//#include <boost/program_options.hpp>

namespace Proto {

class Droppin;
class World;
class Renderer;

class EditInput;
class EditText;

enum class RenderType;
enum class Textures;

class Game {
public:
    Game(/*boost::program_options::variables_map*/);
    ~Game();
    int run();

private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::View viewport;

    std::unique_ptr<AnimatedPlayer> player;

    ///< Window size.
    const int WIN_WIDTH{ 800 };
    const int WIN_HEIGHT{ 600 };
    int framelimit;

    Level level_info; ///< Keeps current level.

    std::unique_ptr<World> world; ///< World object => Updates maps & events according to Level.
    std::unique_ptr<Renderer> renderer; ///< Renderer object => Draws the graphical layout, textures.

    ///! Used as temporary object for Map editing.
    MapObject temp_obj;
    sf::Vector2f edit_mouse;
    bool edit_draw{ false };

    bool editor{ false };

    enum class TempObjType { None, Map, Event, Deco } temp_obj_type;

    ///
    // Used to print out information about objects.
    ///
    std::vector<std::unique_ptr<EditText>> vec_texts;
    bool show_edit_texts{ false };

    sf::Text aloitusteksti;

    ///
    // Layout management
    // vec_inputs : Contains the controls to take the
    // required input.
    // temp_lay : Temporary layout object which
    // which gets constructed at each step of new input.
    // active_input : Keeps count of on which input we are
    // currently working on also the index of active_input
    // in vector vec_inputs gets updated.
    // fill_layout : General boolean flag to control the input
    // start and stop.
    ///
    std::vector<std::unique_ptr<EditInput>> vec_inputs;
    Layout temp_lay;
    int active_input{ -1 };
    bool fill_layout{ false };

    ///
    // Decoration management
    ///
    std::vector<std::unique_ptr<EditInput>> deco_inputs;
    sf::Vector2f temp_deco_pos;
    int deco_input{ -1 };
    bool fill_deco{ false };


    ///< Creates a player GameObject.
    std::unique_ptr<GameObject> create_player();

    /*!
     *\brief
     * Wraps std::stoi function to handle invalid_argument
     * exception and returns boolean accordingly if the
     * exception is thrown.
     */
    std::function<bool(const std::string&, int&)> p_stoi{
        [](const std::string &str, int &result) -> bool {
            try {
                result = std::stoi(str);
            } catch(std::invalid_argument &e) {
                return false;
            }

            return true;
        }
    };

    void editor_input(sf::Event&); ///< Editing maps.
    void handle_input(sf::Event&);
    void update(sf::Time);
    void draw();

    void editor_init(); ///< Initializes the Editor.
    void editor_add_obj(); ///< Adds map object into *map.
    void editor_rotate_obj(sf::Event&); ///< Rotate the map object.
    void editor_create_platform(); ///< Creates event object out of MapObject.
    void editor_reset_temp();       ///< Resets the temporary object.

    void editor_renderer_add_layout();
    void editor_renderer_add_decoration();

    void editor_renderer_init_obj_info();
    void editor_renderer_init_inputs();
    void editor_renderer_update_lay_inputs();
    void editor_renderer_update_text();
    void editor_renderer_draw_text();

    //void parse_cmd(boost::program_options::variables_map&);
    void reset_game();
    void reset_player();
};

}

#endif
