#ifndef ENEMYCNTRL_h
#define ENEMYCNTRL_h

#include "core/hndlrs/alien_cntrl.h"
#include "core/hndlrs/bomber_cntrl.h"
#include "core/hndlrs/destroyer_cntrl.h"

#include "core/game/shots_cntrl.h"
#include "core/score_cntrl.h"

#define ENEMY_CNTRL_GO_RIGHT 0
#define ENEMY_CNTRL_GO_LEFT 1
#define ENEMY_CNTRL_GO_DOWN 2

#define ENEMY_ALIEN_POINT_MUL 3
#define ENEMY_BOMBER_POINT_MUL 2
#define ENEMY_DESTROYER_POINT_MUL 1

#define ENEMY_CNTRL_GO_DOWN_STEPS 3

#define ENEMY_CNTRL_DEF_ENT_AMNT 50

struct enemy_cntrl_ctx {
  struct bomber_cntrl_ctx **bombers;
  struct alien_cntrl_ctx **aliens;

  struct destroyer_cntrl_ctx **destroyers;
  struct enemy_shots_cntrl_ctx *e_shots_ctx;
};

struct enemy_cntrl_ctx *
init_enemy_cntrl_ctx(struct bomber_cntrl_ctx **bomber_ctx,
                     struct alien_cntrl_ctx **alien_ctx,
                     struct destroyer_cntrl_ctx **destroyer_ctx);
int free_enemy_cntrl_ctx(struct enemy_cntrl_ctx *ctx);

int enemy_cntrl_move_right(struct enemy_cntrl_ctx *ctx);
int enemy_cntrl_move_left(struct enemy_cntrl_ctx *ctx);

int enemy_cntrl_move_down(struct enemy_cntrl_ctx *ctx);
int enemy_cntrl_loop(struct game_cntrl_ctx *ctx, Settings *settings,
                     uint8_t *stop);

int enemy_cntrl_check_hit(struct enemy_cntrl_ctx *ctx,
                          struct score_cntrl_ctx *score_ctx, Shot *shot,
                          uint8_t type);
int enemy_cntrl_check_alives(struct enemy_cntrl_ctx *ctx);

#endif
