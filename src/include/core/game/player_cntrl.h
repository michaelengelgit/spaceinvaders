#ifndef PLAYERCNTRL_H
#define PLAYERCNTRL_H

#include <inttypes.h>
#include "types/player.h"

#include "core/game/shots_cntrl.h"

#define PLAYER_CNTRL_DEF_D_SHOTS 100
#define PLAYER_CNTRL_DEF_B_SHOTS 70
#define PLAYER_CNTRL_DEF_N_SHOTS 30

struct player_cntrl_ctx {
  Player player;
  struct player_shots_cntrl_ctx *shots_ctx;

  int key_p;
  uint8_t *lives;
};

struct player_cntrl_ctx *init_player_cntrl(uint8_t *lives, int x, int y);
int free_player_cntrl(struct player_cntrl_ctx *ctx);

int player_cntrl_draw(struct player_cntrl_ctx *ctx);
int player_cntrl_check_hit(struct player_cntrl_ctx *ctx,
                           struct score_cntrl_ctx *score_ctx, Shot *shot);

#endif
