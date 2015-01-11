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

using Proto::Game;

int main(int argc, char *argv[])
{
    bool editor{ false };

    if(argc > 1) {
        std::string arg{ argv[1] };

        if(arg == "--edit")
            editor = true;
    }

    editor == true ? std::cout << "Edit mode\n" : std::cout << "Game mode\n";

    Game game(editor);
    return game.run(); // Run the game application.
}
