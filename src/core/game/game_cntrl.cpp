#include <thread>
#include <unistd.h>

#include "app/end_screen.h"
#include "app/pause_screen.h"
#include "app/won_screen.h"

#include "core/utils.h"
#include "io/toml.h"

#include "core/game/game_cntrl.h"

struct game_cntrl_ctx *init_game(Settings *settings, uint32_t t_score,
                                 uint8_t p_lives) {
  struct game_cntrl_ctx *ctx =
      (struct game_cntrl_ctx *)malloc(sizeof(game_cntrl_ctx));
  if (ctx == NULL)
    return NULL;

  if (t_score > 0 || p_lives > 0) {
    ctx->game_dta.score = t_score;
    ctx->game_dta.lives = p_lives;
  }

  else {
    ctx->game_dta.score = 0;
    ctx->game_dta.lives = 3;
  }

  ctx->shot_dta.shots = 3;
  ctx->shot_dta.bombs = 2;

  ctx->shot_dta.nukes = 1;

  ctx->_game_cntrl.enemy_finish = 0;
  ctx->_game_cntrl.win = GAME_CNTRL_NWON;

  ctx->_game_cntrl.pause = GAME_CNTRL_PAUSE_DEACITVE;
  ctx->_game_cntrl.stop_thr = GAME_CNTRL_ENABLE_THREAD;

  ctx->player_ctx =
      init_player_cntrl(&(ctx->game_dta.lives), COLS / 2, LINES - 1);
  if (ctx->player_ctx == NULL)
    return NULL;

  ctx->aliens_ctx =
      init_alien_cntrl(calc_cnt(COLS, ALIEN_LENGTH, ALIEN_CNTRL_MIN_GAP_CNT));
  if (ctx->aliens_ctx == NULL)
    return NULL;

  ctx->bomber_ctx = init_bomber_cntrl(
      calc_cnt(COLS, BOMBER_LENGTH, BOMBER_CNTRL_MIN_GAP_CNT));
  if (ctx->bomber_ctx == NULL)
    return NULL;

  ctx->destroyers_ctx = init_destroyer_cntrl(
      calc_cnt(COLS, DESTROYER_LENGTH, DESTROYER_CNTRL_MIN_GAP_CNT));
  if (ctx->destroyers_ctx == NULL)
    return NULL;

  ctx->pwalls_ctx =
      init_pwall_cntrl(settings->get_pwall_cnt(), settings->get_pwall_live());
  if (ctx->bomber_ctx == NULL)
    return NULL;

  ctx->score_ctx = init_score_cntrl(
      &(ctx->game_dta.score), &(ctx->game_dta.lives), &(ctx->shot_dta.shots),
      &(ctx->shot_dta.bombs), &(ctx->shot_dta.nukes));
  if (ctx->score_ctx == NULL)
    return NULL;

  ctx->enmy_ctx = init_enemy_cntrl_ctx(&(ctx->bomber_ctx), &(ctx->aliens_ctx),
                                       &(ctx->destroyers_ctx));
  if (ctx->enmy_ctx == NULL)
    return NULL;

  return ctx;
}

int free_game(struct game_cntrl_ctx **ctx) {
  if (*ctx == NULL)
    return -EXIT_FAILURE;

  if (free_player_cntrl((*ctx)->player_ctx) != EXIT_SUCCESS) {
    return -2;
  }

  if (free_bomber_cntrl((*ctx)->bomber_ctx) != EXIT_SUCCESS) {
    return -3;
  }

  if (free_alien_cntrl((*ctx)->aliens_ctx) != EXIT_SUCCESS) {
    return -4;
  }

  if (free_destroyer_cntrl((*ctx)->destroyers_ctx) != EXIT_SUCCESS) {
    return -5;
  }

  if (free_pwall_cntrl((*ctx)->pwalls_ctx) != EXIT_SUCCESS) {
    return -6;
  }

  if (free_score_cntrl((*ctx)->score_ctx) != EXIT_SUCCESS) {
    return -7;
  }

  if (free_enemy_cntrl_ctx((*ctx)->enmy_ctx) != EXIT_SUCCESS) {
    return -8;
  }

  free(*ctx);
  *ctx = NULL;

  return EXIT_SUCCESS;
}

int check_lost(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  if (ctx->game_dta.lives == 0) {
    return EXIT_FAILURE;
  }

  else if (ctx->_game_cntrl.enemy_finish == 1) {
    return EXIT_FAILURE;
  }

  else {
    return EXIT_SUCCESS;
  }
}

int check_won(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  if (enemy_cntrl_check_alives(ctx->enmy_ctx) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  else {
    return EXIT_SUCCESS;
  }
}

int _game_loop(struct game_cntrl_ctx *ctx, Settings *settings) {
  int ret;

  std::thread enmy_t(enemy_cntrl_loop, ctx, settings,
                     &(ctx->_game_cntrl.stop_thr));
  std::thread shts_update_shots_t(shots_cntrl_update_shots, ctx, settings,
                                  &(ctx->_game_cntrl.stop_thr));
  std::thread shts_enmy_shot_t(shots_cntrl_enemy_shot_loop, ctx,
                               &(ctx->_game_cntrl.stop_thr));

start_loop:

  while (1) {
    if (check_lost(ctx) == EXIT_FAILURE) {
    end:

      if (ctx->_game_cntrl.pause == GAME_CNTRL_PAUSE_ACITVE) {
        ctx->_game_cntrl.pause = GAME_CNTRL_PAUSE_DEACITVE;
      }

      ctx->_game_cntrl.stop_thr = GAME_CNTRL_STOP_THREAD;

      shts_enmy_shot_t.join();
      shts_update_shots_t.join();
      enmy_t.join();

      if (settings->check_new_high_score(ctx->game_dta.score) == EXIT_SUCCESS) {
        toml_write_settings(settings);
      }

      ret = end_screen_loop(ctx->game_dta.score);
      goto ret;
    }

    if (check_won(ctx) == EXIT_FAILURE) {
      ctx->_game_cntrl.stop_thr = GAME_CNTRL_STOP_THREAD;

      shts_enmy_shot_t.join();
      shts_update_shots_t.join();
      enmy_t.join();

      if (settings->check_new_high_score(ctx->game_dta.score) == EXIT_SUCCESS) {
        toml_write_settings(settings);
      }

      ret = won_screen_loop(ctx->game_dta.score, ctx->game_dta.lives);
      goto ret;
    }

    switch (getch()) {

    case KEY_LEFT:
    case KEY_a:
      ctx->player_ctx->player.mv_l();
      break;

    case KEY_RIGHT:
    case KEY_d:
      ctx->player_ctx->player.mv_r();
      break;

    case KEY_SPACE:
      player_shot_set(ctx, SHOT_CNTRL_DEFAULT_SHOT);
      break;

    case KEY_b:
      player_shot_set(ctx, SHOT_CNTRL_BOMB_SHOT);
      break;

    case KEY_n:
      player_shot_set(ctx, SHOT_CNTRL_NUKE_SHOT);
      break;

    case KEY_p:
      ctx->_game_cntrl.pause = GAME_CNTRL_PAUSE_ACITVE;

      switch (pause_game(ctx)) {

      case EXIT_QUIT_GAME:
        goto end;

      case EXIT_CONTINUE_GAME:
        goto start_loop;

      default:
        break;
      }

    case KEY_q:
      goto end;

    default:
      break;
    }

    refresh();
  }

ret:

  clear();
  refresh();

  return ret;
}

int start_game(struct game_cntrl_ctx *ctx, Settings *settings) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  clear();
  refresh();

  if (score_cntrl_draw(ctx->score_ctx) != EXIT_SUCCESS) {
    return -2;
  }

  if (player_cntrl_draw(ctx->player_ctx) != EXIT_SUCCESS) {
    return -4;
  }

  if (alien_cntrl_draw(ctx->aliens_ctx) != EXIT_SUCCESS) {
    return -5;
  }

  if (bomber_cntrl_draw(ctx->bomber_ctx) != EXIT_SUCCESS) {
    return -5;
  }

  if (destroyer_cntrl_draw(ctx->destroyers_ctx) != EXIT_SUCCESS) {
    return -6;
  }

  if (pwall_cntrl_draw(ctx->pwalls_ctx) != EXIT_SUCCESS) {
    return -7;
  }

  refresh();
  return _game_loop(ctx, settings);
}

int pause_game(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  refresh();
  clear();
  refresh();

  switch (pause_screen_loop()) {

  case EXIT_QUIT_GAME:
    return EXIT_QUIT_GAME;

  case EXIT_CONTINUE_GAME:
    continue_game(ctx);
    return EXIT_CONTINUE_GAME;

  case -EXIT_FAILURE:
    return -2;

  default:
    return -3;
  }

  return -4;
}

int continue_game(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  clear();
  refresh();

  if (score_cntrl_draw(ctx->score_ctx) != EXIT_SUCCESS) {
    return -2;
  }

  refresh();

  if (player_cntrl_draw(ctx->player_ctx) != EXIT_SUCCESS) {
    return -4;
  }

  refresh();

  if (alien_cntrl_redraw(ctx->aliens_ctx) != EXIT_SUCCESS) {
    return -5;
  }

  refresh();

  if (bomber_cntrl_redraw(ctx->bomber_ctx) != EXIT_SUCCESS) {
    return -5;
  }

  refresh();

  if (destroyer_cntrl_redraw(ctx->destroyers_ctx) != EXIT_SUCCESS) {
    return -6;
  }

  refresh();

  if (pwall_cntrl_redraw(ctx->pwalls_ctx) != EXIT_SUCCESS) {
    return -7;
  }

  refresh();
  usleep(GAME_CNTRL_DEF_CONTINUE_DLY);

  ctx->_game_cntrl.pause = 0;
  return EXIT_SUCCESS;
}
