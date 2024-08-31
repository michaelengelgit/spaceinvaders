#ifndef ALIENCNTRL_H
#define ALIENCNTRL_H

#include "types/alien.h"
#include "types/shot.h"

#define ALIEN_CNTRL_MIN_GAP_CNT 5
#define ALIEN_CNTRL_SPWAN_HEIGHT 4
#define MIN_ALIEN_CNT_SIZE 1

struct alien_cntrl_ctx {
  Alien *aliens;
  int cnt;
};

struct alien_cntrl_ctx *init_alien_cntrl(int cnt);
int free_alien_cntrl(struct alien_cntrl_ctx *ctx);

int alien_cntrl_draw(struct alien_cntrl_ctx *ctx);
int alien_cntrl_redraw(struct alien_cntrl_ctx *ctx);

int alien_cntrl_check_hit(struct alien_cntrl_ctx *ctx,
                          struct score_cntrl_ctx *score_ctx, Shot *shot,
                          uint8_t type);

#endif
