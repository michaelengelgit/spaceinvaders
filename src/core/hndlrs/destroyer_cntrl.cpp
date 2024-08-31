#include <ncurses.h>

#include "core/game/enemy_cntrl.h"

#include "core/hndlrs/destroyer_cntrl.h"

struct destroyer_cntrl_ctx *init_destroyer_cntrl(int cnt) {
  struct destroyer_cntrl_ctx *ctx =
      (struct destroyer_cntrl_ctx *)malloc(sizeof(destroyer_cntrl_ctx));

  if (ctx == NULL)
    return NULL;

  if (cnt < MIN_DESTORYER_CNT_SIZE)
    return NULL;

  ctx->destroyers = (Destroyer *)malloc(sizeof(Destroyer) * cnt);
  if (ctx->destroyers == NULL)
    return NULL;

  ctx->cnt = cnt;
  return ctx;
}

int free_destroyer_cntrl(struct destroyer_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {
    ctx->destroyers[i].clean(0);
  }

  if (ctx->destroyers) {
    free(ctx->destroyers);
  }

  free(ctx);
  return EXIT_SUCCESS;
}

int destroyer_cntrl_draw(struct destroyer_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {
    int dx = (i * 8) + ((COLS / 2) - ((ctx->cnt / 2) * 8));

    ctx->destroyers[i] =
        Destroyer(dx, DESTROYER_CNTRL_SPWAN_HEIGHT, DESTROYER_ALIVE);
    ctx->destroyers[i].draw();
  }

  return EXIT_SUCCESS;
}

int destroyer_cntrl_redraw(struct destroyer_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {

    if (ctx->destroyers[i].get_alive()) {
      ctx->destroyers[i].draw();
    }
  }

  return EXIT_SUCCESS;
}

int destroyer_cntrl_check_hit(struct destroyer_cntrl_ctx *ctx,
                              struct score_cntrl_ctx *score_ctx, Shot *shot,
                              uint8_t type) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  if (score_ctx == NULL)
    return -2;

  for (int i = 0; i < ctx->cnt; i++) {
    Destroyer *_destroyer = &(ctx->destroyers[i]);

    if (_destroyer->get_alive() == 1) {

      if (_destroyer->check_hit(shot->get_x(), shot->get_y()) == EXIT_FAILURE) {

        switch (type) {

        case SHOT_CNTRL_DEFAULT_SHOT:
          _destroyer->set_unalive();

          score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_DESTROYER_POINT_MUL);
          break;

        case SHOT_CNTRL_BOMB_SHOT:
          _destroyer->set_unalive();
          score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_DESTROYER_POINT_MUL);

          if (i < ctx->cnt - 1) {

            if (ctx->destroyers[i + 1].get_alive()) {

              ctx->destroyers[i + 1].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_DESTROYER_POINT_MUL);
            }
          }

          if (i > 1) {

            if (ctx->destroyers[i - 1].get_alive()) {

              ctx->destroyers[i - 1].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_DESTROYER_POINT_MUL);
            }
          }

          break;

        case SHOT_CNTRL_NUKE_SHOT:
          _destroyer->set_unalive();
          score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_DESTROYER_POINT_MUL);

          if (i < ctx->cnt - 1) {

            if (ctx->destroyers[i + 1].get_alive()) {

              ctx->destroyers[i + 1].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_DESTROYER_POINT_MUL);
            }
          }

          if (i > 1) {

            if (ctx->destroyers[i - 1].get_alive()) {

              ctx->destroyers[i - 1].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_DESTROYER_POINT_MUL);
            }
          }

          if (i < ctx->cnt - 2) {

            if (ctx->destroyers[i + 2].get_alive()) {

              ctx->destroyers[i + 2].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_DESTROYER_POINT_MUL);
            }
          }

          if (i > 2) {

            if (ctx->destroyers[i - 2].get_alive()) {

              ctx->destroyers[i - 2].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_DESTROYER_POINT_MUL);
            }
          }

          break;

        default:
          return -2;
        }

        return EXIT_FAILURE;
      }
    }
  }

  return EXIT_SUCCESS;
}
