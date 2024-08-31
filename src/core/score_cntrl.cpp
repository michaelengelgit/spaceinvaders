#include <ncurses.h>
#include <stdlib.h>

#include "core/score_cntrl.h"

struct score_cntrl_ctx *init_score_cntrl(uint32_t *score, uint8_t *lives,
                                         uint8_t *shots, uint8_t *bombs,
                                         uint8_t *nukes) {
  struct score_cntrl_ctx *ctx =
      (struct score_cntrl_ctx *)malloc(sizeof(struct score_cntrl_ctx));
  if (ctx == NULL)
    return NULL;

  ctx->score = score;
  ctx->lives = lives;

  ctx->shots = shots;
  ctx->bombs = bombs;

  ctx->nukes = nukes;
  return ctx;
}

int free_score_cntrl(struct score_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  free(ctx);
  return EXIT_SUCCESS;
}

int score_cntrl_draw(struct score_cntrl_ctx *ctx) {

  clear();
  refresh();

  move(0, (COLS / 2) - SCORE_OFFSET_ONE);
  addstr(SCORE_GAME_NAME);

  move(0, 1);
  addstr(SCORE_SCORE_TITLE);

  move(0, 17);
  addstr(SCORE_LIFE_TITLE);

  move(0, 17 + 7);
  for (int i = 0; i < *(ctx->lives); i++) {
    move(0, 17 + 7 + i);
    addch('X');
  }

  move(0, 31);
  addstr(SCORE_SHOTS_TITLE);

  move(0, 31 + 7);
  for (int i = 0; i < *(ctx->shots); i++) {
    move(0, 31 + 7 + i);
    addch('X');
  }

  move(0, 45);
  addstr(SCORE_BOMBS_TITLE);

  move(0, 45 + 7);
  for (int i = 0; i < *(ctx->bombs); i++) {
    move(0, 45 + 7 + i);
    addch('X');
  }

  move(0, 59);
  addstr(SCORE_NUKE_TITLE);

  move(0, 59 + 7);
  for (int i = 0; i < *(ctx->nukes); i++) {
    move(0, 59 + 7 + i);
    addch('X');
  }

  move(0, COLS - SCORE_OFFSET_TWO);
  addstr(SCORE_SETTING_TITLE);

  move(0, 8);
  sprintf(ctx->tscore, "%d", *(ctx->score));
  move(0, 8);

  addstr(ctx->tscore);

  refresh();
  return EXIT_SUCCESS;
}

int score_cntrl_add_p(struct score_cntrl_ctx *ctx, int p) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  *(ctx->score) += p;

  move(0, 8);
  addstr("     ");

  sprintf(ctx->tscore, "%d", *(ctx->score));

  move(0, 8);
  addstr(ctx->tscore);

  return EXIT_SUCCESS;
}

int score_cntrl_update_shot(struct score_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  move(0, 31 + 7);
  addstr("     ");

  for (int i = 0; i < *(ctx->shots); i++) {
    move(0, 31 + 7 + i);
    addch('X');
  }

  return EXIT_SUCCESS;
}

int score_cntrl_update_bomb(struct score_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  move(0, 45 + 7);
  addstr("    ");

  for (int i = 0; i < *(ctx->bombs); i++) {
    move(0, 45 + 7 + i);
    addch('X');
  }

  return EXIT_SUCCESS;
}

int score_cntrl_update_nuke(struct score_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  move(0, 59 + 7);
  addstr("    ");

  for (int i = 0; i < *(ctx->nukes); i++) {
    move(0, 59 + 7 + i);
    addch('X');
  }

  return EXIT_SUCCESS;
}

int score_cntrl_update_live(struct score_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  move(0, 17 + 7);
  addstr("     ");

  for (int i = 0; i < *(ctx->lives); i++) {
    move(0, 17 + 7 + i);
    addch('X');
  }

  return EXIT_SUCCESS;
}
