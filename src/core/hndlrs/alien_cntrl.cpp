#include <ncurses.h>

#include "core/game/enemy_cntrl.h"

#include "core/hndlrs/alien_cntrl.h"

struct alien_cntrl_ctx *init_alien_cntrl(int cnt) {
  struct alien_cntrl_ctx *ctx =
      (struct alien_cntrl_ctx *)malloc(sizeof(alien_cntrl_ctx));
  if (ctx == NULL)
    return NULL;

  if (cnt < MIN_ALIEN_CNT_SIZE)
    return NULL;

  ctx->aliens = (Alien *)malloc(sizeof(Alien) * cnt);
  if (ctx->aliens == NULL)
    return NULL;

  ctx->cnt = cnt;
  return ctx;
}

int free_alien_cntrl(struct alien_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {
    ctx->aliens[i].clean(0);
  }

  if (ctx->aliens) {
    free(ctx->aliens);
  }

  free(ctx);
  return EXIT_SUCCESS;
}

int alien_cntrl_draw(struct alien_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {
    int dx = (i * 8) + ((COLS / 2) - ((ctx->cnt / 2) * 8));

    ctx->aliens[i] = Alien(dx, ALIEN_CNTRL_SPWAN_HEIGHT, ALIEN_ALIVE);
    ctx->aliens[i].draw();
  }

  return EXIT_SUCCESS;
}

int alien_cntrl_redraw(struct alien_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < ctx->cnt; i++) {

    if (ctx->aliens[i].get_alive()) {
      ctx->aliens[i].draw();
    }
  }

  return EXIT_SUCCESS;
}

int alien_cntrl_check_hit(struct alien_cntrl_ctx *ctx,
                          struct score_cntrl_ctx *score_ctx, Shot *shot,
                          uint8_t type) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  if (score_ctx == NULL)
    return -2;

  for (int i = 0; i < ctx->cnt; i++) {
    Alien *_alien = &(ctx->aliens[i]);

    if (_alien->get_alive()) {

      if (_alien->check_hit(shot->get_x(), shot->get_y()) == EXIT_FAILURE) {

        switch (type) {

        case SHOT_CNTRL_DEFAULT_SHOT:
          _alien->set_unalive();

          score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_ALIEN_POINT_MUL);
          break;

        case SHOT_CNTRL_BOMB_SHOT:
          _alien->set_unalive();
          score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_ALIEN_POINT_MUL);

          if (i < ctx->cnt - 1) {

            if (ctx->aliens[i + 1].get_alive()) {

              ctx->aliens[i + 1].set_unalive();
              score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_ALIEN_POINT_MUL);
            }
          }

          if (i > 1) {

            if (ctx->aliens[i - 1].get_alive()) {

              ctx->aliens[i - 1].set_unalive();
              score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_ALIEN_POINT_MUL);
            }
          }

          break;

        case SHOT_CNTRL_NUKE_SHOT:
          _alien->set_unalive();
          score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_ALIEN_POINT_MUL);

          if (i < ctx->cnt - 1) {

            if (ctx->aliens[i + 1].get_alive()) {

              ctx->aliens[i + 1].set_unalive();
              score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_ALIEN_POINT_MUL);
            }
          }

          if (i > 1) {

            if (ctx->aliens[i - 1].get_alive()) {

              ctx->aliens[i - 1].set_unalive();
              score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_ALIEN_POINT_MUL);
            }
          }

          if (i < ctx->cnt - 2) {

            if (ctx->aliens[i + 2].get_alive()) {

              ctx->aliens[i + 2].set_unalive();
              score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_ALIEN_POINT_MUL);
            }
          }

          if (i > 2) {

            if (ctx->aliens[i - 2].get_alive()) {

              ctx->aliens[i - 2].set_unalive();
              score_cntrl_add_p(score_ctx, SHOT_POINTS * ENEMY_ALIEN_POINT_MUL);
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
