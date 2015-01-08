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

using Proto::Game;

int main(int argc, char *argv[])
{
    Game game; //(argc, argv);
    return game.run(); // Run the game application.
}
