#ifndef PWALLCNTRL_H
#define PWALLCNTRL_H

#include <ncurses.h>

#include "types/pwall.h"
#include "types/shot.h"

#define PWALL_BORDER_DISTANCE 6
#define PWALL_CNTRL_SPWAN_HEIGHT LINES - PWALL_BORDER_DISTANCE

struct pwall_cntrl_ctx {
  Pwall *pwalls;
  int cnt;

  int live;
};

struct pwall_cntrl_ctx *init_pwall_cntrl(int cnt, int live);
int free_pwall_cntrl(struct pwall_cntrl_ctx *ctx);

int pwall_cntrl_draw(struct pwall_cntrl_ctx *ctx);
int pwall_cntrl_redraw(struct pwall_cntrl_ctx *ctx);

int pwall_cntrl_check_hit(struct pwall_cntrl_ctx *ctx, Shot *shot);

#endif
