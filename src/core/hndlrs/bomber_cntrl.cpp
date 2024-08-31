#include <ncurses.h>

#include "core/game/enemy_cntrl.h"

#include "core/hndlrs/bomber_cntrl.h"

struct bomber_cntrl_ctx *init_bomber_cntrl(int cnt) {
  struct bomber_cntrl_ctx *ctx =
      (struct bomber_cntrl_ctx *)malloc(sizeof(bomber_cntrl_ctx));
  if (ctx == NULL)
    return NULL;

  if (cnt < MIN_BOMBER_CNT_SIZE)
    return NULL;

  ctx->bomber = (Bomber *)malloc(sizeof(Bomber) * cnt);
  if (ctx->bomber == NULL)
    return NULL;

  ctx->cnt = cnt;
  return ctx;
}

int free_bomber_cntrl(struct bomber_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {
    ctx->bomber[i].clean(0);
  }

  if (ctx->bomber) {
    free(ctx->bomber);
  }

  free(ctx);
  return EXIT_SUCCESS;
}

int bomber_cntrl_draw(struct bomber_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {
    int dx = (i * 8) + ((COLS / 2) - ((ctx->cnt / 2) * 8));

    ctx->bomber[i] = Bomber(dx, BOMBER_CNTRL_SPWAN_HEIGHT, BOMBER_ALIVE);
    ctx->bomber[i].draw();
  }

  return EXIT_SUCCESS;
}

int bomber_cntrl_redraw(struct bomber_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {

    if (ctx->bomber[i].get_alive()) {
      ctx->bomber[i].draw();
    }
  }

  return EXIT_SUCCESS;
}

int bomber_cntrl_check_hit(struct bomber_cntrl_ctx *ctx,
                           struct score_cntrl_ctx *score_ctx, Shot *shot,
                           uint8_t type) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  if (score_ctx == NULL)
    return -2;

  for (int i = 0; i < ctx->cnt; i++) {
    Bomber *_bomber = &(ctx->bomber[i]);

    if (_bomber->get_alive()) {

      if (_bomber->check_hit(shot->get_x(), shot->get_y()) == EXIT_FAILURE) {

        switch (type) {

        case SHOT_CNTRL_DEFAULT_SHOT:
          _bomber->set_unalive();

          score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_BOMBER_POINT_MUL);
          break;

        case SHOT_CNTRL_BOMB_SHOT:
          _bomber->set_unalive();
          score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_BOMBER_POINT_MUL);

          if (i < ctx->cnt - 1) {

            if (ctx->bomber[i + 1].get_alive()) {

              ctx->bomber[i + 1].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_BOMBER_POINT_MUL);
            }
          }

          if (i > 1) {

            if (ctx->bomber[i - 1].get_alive()) {

              ctx->bomber[i - 1].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_BOMBER_POINT_MUL);
            }
          }

          break;

        case SHOT_CNTRL_NUKE_SHOT:
          _bomber->set_unalive();
          score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_BOMBER_POINT_MUL);

          if (i < ctx->cnt - 1) {

            if (ctx->bomber[i + 1].get_alive()) {

              ctx->bomber[i + 1].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_BOMBER_POINT_MUL);
            }
          }

          if (i > 1) {

            if (ctx->bomber[i - 1].get_alive()) {

              ctx->bomber[i - 1].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_BOMBER_POINT_MUL);
            }
          }

          if (i < ctx->cnt - 2) {

            if (ctx->bomber[i + 2].get_alive()) {

              ctx->bomber[i + 2].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_BOMBER_POINT_MUL);
            }
          }

          if (i > 2) {

            if (ctx->bomber[i - 2].get_alive()) {

              ctx->bomber[i - 2].set_unalive();
              score_cntrl_add_p(score_ctx,
                                SHOT_POINTS * ENEMY_BOMBER_POINT_MUL);
            }
          }

          break;

        default:
          return -3;
        }

        return EXIT_FAILURE;
      }
    }
  }

  return EXIT_SUCCESS;
}
