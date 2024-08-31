#include <cstdlib>
#include <ncurses.h>
#include <stdio.h>

#include "core/game/player_cntrl.h"
#include "core/utils.h"

#define TEST_X COLS / 2
#define TEST_Y LINES / 2

#define EXIT_ERROR_DRAW 2
#define EXIT_ERROR_FREE 3

int main() {

  uint8_t lives = 3;

  struct player_cntrl_ctx *player_ctx =
      init_player_cntrl(&lives, TEST_X, TEST_Y);
  if (player_ctx == NULL)
    return -EXIT_FAILURE;

  __init_scr();

  if (player_cntrl_draw(player_ctx) != EXIT_SUCCESS) {
    return -EXIT_ERROR_DRAW;
  }

  if (free_player_cntrl(player_ctx) == EXIT_FAILURE) {
    return -EXIT_ERROR_FREE;
  }

  __free_scr();

  return EXIT_SUCCESS;
}
