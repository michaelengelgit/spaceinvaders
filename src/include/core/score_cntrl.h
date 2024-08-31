#ifndef SCORECNTRL_H
#define SCORECNTRL_H

#include <inttypes.h>

#define SCORE_GAME_NAME "--SPACE INVADERS--"

#define SCORE_SCORE_TITLE "SCORE: "
#define SCORE_LIFE_TITLE "LIVES: "

#define SCORE_SHOTS_TITLE "SHOTS: "
#define SCORE_BOMBS_TITLE "BOMBS: "
#define SCORE_NUKE_TITLE "NUKES: "

#define SCORE_SETTING_TITLE "p = pause || q = quit"

#define SCORE_OFFSET_ONE 9
#define SCORE_OFFSET_TWO 21

#define SHOT_POINTS 5

struct score_cntrl_ctx {
  char tscore[30];
  uint32_t *score;

  uint8_t *lives;
  uint8_t *shots;

  uint8_t *bombs;
  uint8_t *nukes;
};

struct score_cntrl_ctx *init_score_cntrl(uint32_t *score, uint8_t *lives,
                                         uint8_t *shots, uint8_t *bombs,
                                         uint8_t *nukes);
int free_score_cntrl(struct score_cntrl_ctx *ctx);

int score_cntrl_draw(struct score_cntrl_ctx *ctx);
int score_cntrl_add_p(struct score_cntrl_ctx *ctx, int p);

int score_cntrl_update_shot(struct score_cntrl_ctx *ctx);
int score_cntrl_update_bomb(struct score_cntrl_ctx *ctx);

int score_cntrl_update_nuke(struct score_cntrl_ctx *ctx);
int score_cntrl_update_live(struct score_cntrl_ctx *ctx);

#endif
