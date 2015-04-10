#include "Game.h"

/**
 * Build up a simple sandbox for testing.
 * Task list:
 * - Map(File stream).
 * - Component system.
 * -> Milestone
 *      => Maps should be drawn at this point also
 *         implementing some simple gameplay is straight forward.
 *
 * Prototyping mechanics:
 * - Movable environment puzzles.
 *
 */

#include <iostream>
#include <string>
#include <boost/program_options.hpp>

using Proto::Game;
using namespace boost::program_options;

int main(int argc, char *argv[])
{
    variables_map vars; // Stores the cmd variables here.
    try {
        // Parse the command line args with the use of Booost!
        options_description desc("Options");
        desc.add_options()
                ("edit", value<bool>()->default_value(false), "Edit mode")
                ("map", value<std::string>()->default_value("proto.map"), "Map select")
                ("fps", value<int>()->default_value(60), "Framelimit(fps)");

        store(parse_command_line(argc, argv, desc), vars);

    } catch(const error &err) {
        std::cout << err.what() << std::endl;
    }

    Game game(vars);
    return game.run(); // Run the game application.
}
