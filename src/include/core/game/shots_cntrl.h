#ifndef SHOTSCNTRL_H
#define SHOTSCNTRL_H

#include "types/settings.h"
#include "types/shot.h"

#define SHOT_CNTRL_DEF_SHOT_SYM '*'
#define SHOT_CNTRL_DEF_BOMB_SYM '!'
#define SHOT_CNTRL_DEF_NUKE_SYM '$'

#define SHOT_CNTRL_DEF_ALIEN_SHOT_SYM 'X'
#define SHOT_CNTRL_DEF_BOMBER_SHOT_SYM 'V'
#define SHOT_CNTRL_DEF_DESTROYER_SHOT_SYM 'Y'

#define SHOT_CNTRL_DEFAULT_SHOT 1
#define SHOT_CNTRL_BOMB_SHOT 2

#define SHOT_CNTRL_NUKE_SHOT 3
#define SHOT_CNTRL_ALIEN_SHOT 0

#define SHOT_CNTRL_BOMBER_SHOT 1
#define SHOT_CNTRL_DESTROYER_SHOT 2

#define SHOT_CNTRL_ALIEN_BOMBER_SHOT 3
#define SHOT_CNTRL_ALIEN_DESTROYER_SHOT 4

#define SHOT_CNTRL_BOMBER_DESTROYER_SHOT 5
#define SHOT_CNTRL_ALIEN_BOMBER_DESTROYER_SHOT 6

struct player_shots_cntrl_ctx {
  Shot *d_shots;
  uint8_t d_cnt;

  Shot *b_shots;
  uint8_t b_cnt;

  Shot *n_shots;
  uint8_t n_cnt;
};

struct enemy_shots_cntrl_ctx {
  Shot *a_shots;
  uint8_t a_cnt;

  Shot *b_shots;
  uint8_t b_cnt;

  Shot *d_shots;
  uint8_t d_cnt;
};

struct player_shots_cntrl_ctx *init_player_shots_cntrl(int d_cnt, int b_cnt,
                                                       int n_cnt);
struct enemy_shots_cntrl_ctx *init_enemy_shots_cntrl(int a_cnt, int b_cnt,
                                                     int d_cnt);

int free_player_shots_cntrl(struct player_shots_cntrl_ctx *ctx);
int free_enemy_shots_cntrl(struct enemy_shots_cntrl_ctx *ctx);

int player_shot_set(struct game_cntrl_ctx *ctx, uint8_t type);
int enemy_shots_set(struct game_cntrl_ctx *ctx);

int player_shots_move(struct game_cntrl_ctx *ctx);
int enemy_shots_move(struct game_cntrl_ctx *ctx);

int shots_cntrl_update_shots(struct game_cntrl_ctx *ctx, Settings *settings,
                             uint8_t *stop);
int shots_cntrl_enemy_shot_loop(struct game_cntrl_ctx *ctx, uint8_t *stop);

#endif
