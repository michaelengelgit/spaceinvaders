#include <stdlib.h>

#include "core/hndlrs/pwall_cntrl.h"

struct pwall_cntrl_ctx *init_pwall_cntrl(int cnt, int live) {
  struct pwall_cntrl_ctx *ctx =
      (struct pwall_cntrl_ctx *)malloc(sizeof(pwall_cntrl_ctx));
  if (ctx == NULL)
    return NULL;

  ctx->pwalls = (Pwall *)malloc(sizeof(Pwall) * cnt);
  if (ctx->pwalls == NULL)
    return NULL;

  ctx->cnt = cnt;
  ctx->live = live;

  return ctx;
}

int free_pwall_cntrl(struct pwall_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {
    ctx->pwalls[i].clean();
  }

  free(ctx->pwalls);
  free(ctx);

  return EXIT_SUCCESS;
}

int pwall_cntrl_draw(struct pwall_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {

    int rm = COLS % ctx->cnt;
    int nx;

    if (rm != 0) {
      nx = (COLS - rm) / ctx->cnt;

    } else {
      nx = COLS / ctx->cnt;
    }

    int nnx = nx / 2;

    ctx->pwalls[i] = Pwall(nnx + (nx * i), PWALL_CNTRL_SPWAN_HEIGHT, ctx->live);
    ctx->pwalls[i].draw();
  }

  return EXIT_SUCCESS;
}

int pwall_cntrl_redraw(struct pwall_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {
    ctx->pwalls[i].draw();
  }

  return EXIT_SUCCESS;
}

int pwall_cntrl_check_hit(struct pwall_cntrl_ctx *ctx, Shot *shot) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {
    Pwall *_pwall = &(ctx->pwalls[i]);

    if (_pwall->is_alive()) {

      if (_pwall->check_hit(shot->get_x(), shot->get_y()) == EXIT_FAILURE) {

        _pwall->d_live();
        return EXIT_FAILURE;
      }
    }
  }

  return EXIT_SUCCESS;
}
