#include <stdio.h>

#include "app/help_screen.h"
#include "app/menu_screen.h"
#include "app/start_screen.h"

#include "core/game/game_cntrl.h"
#include "core/utils.h"

#include "io/toml.h"

#define EXIT_ERROR_INIT_GAME 2
#define EXIT_ERROR_START_SCREEN 3
#define EXIT_ERROR_START_GAME 4
#define EXIT_ERROR_FREE_GAME 5
#define EXIT_ERROR_HELP_SCREEN 6
#define EXIT_ERROR_MENU_SCREEN 7

using namespace std;

int main() {
  int ret;

  uint32_t t_score = 0;
  uint8_t p_lives = 0;

  Settings game_settings = settings_init();
  struct game_cntrl_ctx *game_ctx = NULL;

  __init_scr();

start_screen:
  switch (start_screen_loop(game_settings.get_high_score())) {

  case EXIT_START_GAME:
    goto start_game;

  case EXIT_QUIT_GAME:
    goto cleanup;

  case EXIT_HELP_GAME:
    goto help_game;

  case EXIT_MENU_GAME:
    goto menu_game;

  default:
    ret = -EXIT_ERROR_START_SCREEN;
    goto cleanup;
  }

help_game:
  switch (help_screen_loop()) {
  case EXIT_QUIT_GAME:
    goto cleanup;

  case EXIT_MENU_GAME:
    goto menu_game;

  case EXIT_START_MENU:
    goto start_screen;

  default:
    ret = -EXIT_ERROR_HELP_SCREEN;
    goto cleanup;
  }

menu_game:
  switch (menu_screen_loop(&game_settings)) {

  case EXIT_QUIT_GAME:
    goto cleanup;

  case EXIT_START_MENU:
    goto start_screen;

  default:
    ret = -EXIT_ERROR_MENU_SCREEN;
    goto cleanup;
  }

won_game:
  t_score = game_ctx->game_dta.score;
  p_lives = game_ctx->game_dta.lives;

start_game:
  if (free_game(&game_ctx) != EXIT_SUCCESS) {
    ret = -EXIT_ERROR_FREE_GAME;
  }

  game_ctx = init_game(&game_settings, t_score, p_lives);
  if (game_ctx == NULL) {
    ret = -EXIT_ERROR_INIT_GAME;
    goto ret;
  }

  ret = start_game(game_ctx, &game_settings);
  if (ret < EXIT_SUCCESS) {
    ret = -EXIT_ERROR_START_GAME;
    goto cleanup;
  }

  if (ret == -EXIT_FAILURE) {
    goto cleanup;
  }

  switch (ret) {
  case EXIT_QUIT_GAME:
    goto cleanup;

  case EXIT_MENU_GAME:
    t_score = 0;
    p_lives = 0;
    goto menu_game;

  case EXIT_HELP_GAME:
    t_score = 0;
    p_lives = 0;
    goto help_game;

  case EXIT_START_GAME:
    t_score = 0;
    p_lives = 0;
    goto start_game;

  case EXIT_WON_GAME:
    goto won_game;
    break;

  default:
    break;
  }

  ret = EXIT_SUCCESS;

cleanup:
  __free_scr();

  if (free_game(&game_ctx) != EXIT_SUCCESS) {
    ret = -EXIT_ERROR_FREE_GAME;
  }

  else {
    ret = EXIT_SUCCESS;
  }

ret:
  return ret;
}
