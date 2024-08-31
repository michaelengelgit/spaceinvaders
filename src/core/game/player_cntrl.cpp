#include <cstdlib>
#include <stdlib.h>

#include "core/score_cntrl.h"

#include "core/game/player_cntrl.h"

struct player_cntrl_ctx *init_player_cntrl(uint8_t *lives, int x, int y) {
  struct player_cntrl_ctx *ctx =
      (struct player_cntrl_ctx *)malloc(sizeof(struct player_cntrl_ctx));
  if (ctx == NULL)
    return NULL;

  ctx->shots_ctx = init_player_shots_cntrl(PLAYER_CNTRL_DEF_D_SHOTS,
                                           PLAYER_CNTRL_DEF_B_SHOTS,
                                           PLAYER_CNTRL_DEF_N_SHOTS);
  if (ctx->shots_ctx == NULL)
    return NULL;

  ctx->lives = lives;
  ctx->player = Player(x, y);

  return ctx;
}

int free_player_cntrl(struct player_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  if (free_player_shots_cntrl(ctx->shots_ctx) != EXIT_SUCCESS) {
    return -2;
  }

  free(ctx);
  return EXIT_SUCCESS;
}

int player_cntrl_draw(struct player_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  if (ctx->player.draw() != EXIT_SUCCESS) {
    return -2;
  }

  return EXIT_SUCCESS;
}

int player_cntrl_check_hit(struct player_cntrl_ctx *ctx,
                           struct score_cntrl_ctx *score_ctx, Shot *shot) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  if (score_ctx == NULL)
    return -2;

  if (ctx->player.check_hit(shot->get_x(), shot->get_y()) == EXIT_FAILURE) {

    if (*(ctx->lives) > 0) {
      *(ctx->lives) -= 1;

      score_cntrl_update_live(score_ctx);
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
