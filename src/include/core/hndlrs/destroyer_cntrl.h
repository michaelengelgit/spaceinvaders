#ifndef DESTROYERCNTRL_H
#define DESTROYERCNTRL_H

#include <inttypes.h>

#include "types/destroyer.h"
#include "types/shot.h"

#define DESTROYER_CNTRL_MIN_GAP_CNT 5
#define DESTROYER_CNTRL_SPWAN_HEIGHT 12
#define MIN_DESTORYER_CNT_SIZE 1

struct destroyer_cntrl_ctx {
  Destroyer *destroyers;
  int cnt;
};

struct destroyer_cntrl_ctx *init_destroyer_cntrl(int cnt);
int free_destroyer_cntrl(struct destroyer_cntrl_ctx *ctx);

int destroyer_cntrl_draw(struct destroyer_cntrl_ctx *ctx);
int destroyer_cntrl_redraw(struct destroyer_cntrl_ctx *ctx);

int destroyer_cntrl_check_hit(struct destroyer_cntrl_ctx *ctx,
                              struct score_cntrl_ctx *score_ctx, Shot *shot,
                              uint8_t type);

#endif
