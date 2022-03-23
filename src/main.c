// Standard headers
#include <stdio.h>
#include <stdlib.h>

// Internal headers
#include "attacker.h"
#include "defender.h"
#include "dimension.h"
#include "map.h"
#include "game.h"

// Macros
#define STANDARD_FIELD_DIMENSION (dimension_t) { 10, 10 }
#define STANDARD_MAX_NUMBER_SPIES 1LU
#define STANDARD_MAX_TURNS 42

/*----------------------------------------------------------------------------*/
/*                               MAIN FUNCTION                                */
/*----------------------------------------------------------------------------*/

int main(int argc, char** argv) {
  if (argc >= 3) {
    fprintf(stderr, "USAGE: %s [map_path]\n", argv[0]);
    return EXIT_FAILURE;
  }

  printf("## RUGBY GAME ##\n\n");

  Game game = NULL;

  if (argc == 1) {
    game = new_game(
        STANDARD_FIELD_DIMENSION,
        STANDARD_MAX_NUMBER_SPIES,
        execute_attacker_strategy,
        execute_defender_strategy);
  }

  if (argc == 2) {
    Map map = new_map(argv[1]);

    game = new_game_from_map(
        map,
        STANDARD_MAX_NUMBER_SPIES,
        execute_attacker_strategy,
        execute_defender_strategy);

    delete_map(map);
  }

  play_game(game, STANDARD_MAX_TURNS);

  delete_game(game);

  return EXIT_SUCCESS;
}
