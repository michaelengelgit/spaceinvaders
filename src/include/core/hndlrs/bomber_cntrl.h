#ifndef BOMBERCNTRL_H
#define BOMBERCNTRL_H

#include "core/score_cntrl.h"

#include "types/bomber.h"
#include "types/shot.h"

#define BOMBER_CNTRL_MIN_GAP_CNT 5
#define BOMBER_CNTRL_SPWAN_HEIGHT 8
#define MIN_BOMBER_CNT_SIZE 1

struct bomber_cntrl_ctx {
  Bomber *bomber;
  int cnt;
};

struct bomber_cntrl_ctx *init_bomber_cntrl(int cnt);
int free_bomber_cntrl(struct bomber_cntrl_ctx *ctx);

int bomber_cntrl_draw(struct bomber_cntrl_ctx *ctx);
int bomber_cntrl_redraw(struct bomber_cntrl_ctx *ctx);

int bomber_cntrl_check_hit(struct bomber_cntrl_ctx *ctx,
                           struct score_cntrl_ctx *score_ctx, Shot *shot,
                           uint8_t type);

#endif
