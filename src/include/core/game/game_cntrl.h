#ifndef GAMECNTRL_H
#define GAMECNTRL_h

#include <inttypes.h>

#include "core/game/enemy_cntrl.h"
#include "core/game/player_cntrl.h"

#include "core/hndlrs/pwall_cntrl.h"
#include "core/score_cntrl.h"

#define GAME_CNTRL_PAUSE_ACITVE 1
#define GAME_CNTRL_PAUSE_DEACITVE 0

#define GAME_CNTRL_STOP_THREAD 1
#define GAME_CNTRL_ENABLE_THREAD 0

#define GAME_CNTRL_WON 1
#define GAME_CNTRL_NWON 0

#define GAME_CNTRL_DEF_CONTINUE_DLY 300000

struct game_data_ctx {
  uint32_t score;
  uint8_t lives;
};

struct __game_cntrl_ctx {
  uint8_t stop_thr;
  uint8_t pause;

  uint8_t win;
  uint8_t enemy_finish;
};

struct shot_data_ctx {
  uint8_t shots;
  uint8_t bombs;
  uint8_t nukes;
};

struct game_cntrl_ctx {

  WINDOW *scr;

  struct player_cntrl_ctx *player_ctx;
  struct alien_cntrl_ctx *aliens_ctx;

  struct bomber_cntrl_ctx *bomber_ctx;
  struct destroyer_cntrl_ctx *destroyers_ctx;

  struct pwall_cntrl_ctx *pwalls_ctx;
  struct score_cntrl_ctx *score_ctx;

  struct enemy_cntrl_ctx *enmy_ctx;
  struct game_data_ctx game_dta;

  struct shot_data_ctx shot_dta;
  struct __game_cntrl_ctx _game_cntrl;
};

struct game_cntrl_ctx *init_game(Settings *settings, uint32_t t_score,
                                 uint8_t p_lives);
int free_game(struct game_cntrl_ctx **ctx);

int check_lost(struct game_cntrl_ctx *ctx);
int check_won(struct game_cntrl_ctx *ctx);

int start_game(struct game_cntrl_ctx *ctx, Settings *settings);

int pause_game(struct game_cntrl_ctx *ctx);
int continue_game(struct game_cntrl_ctx *ctx);

#endif
