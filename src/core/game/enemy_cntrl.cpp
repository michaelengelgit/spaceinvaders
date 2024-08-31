#include <cstdlib>
#include <unistd.h>

#include "core/game/game_cntrl.h"

#include "core/game/enemy_cntrl.h"

int __check_move_res(int mov, int res, register_t *pv) {
  if (mov == ENEMY_CNTRL_GO_RIGHT && res == EXIT_SUCCESS) {
    return ENEMY_CNTRL_GO_RIGHT;
  }

  if (mov == ENEMY_CNTRL_GO_RIGHT && res == EXIT_FAILURE) {
    *pv = ENEMY_CNTRL_GO_RIGHT;
    return ENEMY_CNTRL_GO_DOWN;
  }

  if (mov == ENEMY_CNTRL_GO_LEFT && res == EXIT_SUCCESS) {
    return ENEMY_CNTRL_GO_LEFT;
  }

  if (mov == ENEMY_CNTRL_GO_LEFT && res == EXIT_FAILURE) {
    *pv = ENEMY_CNTRL_GO_LEFT;
    return ENEMY_CNTRL_GO_DOWN;
  }

  if (mov == ENEMY_CNTRL_GO_DOWN) {
    return ENEMY_CNTRL_GO_DOWN;
  }

  return -EXIT_FAILURE;
}

struct enemy_cntrl_ctx *
init_enemy_cntrl_ctx(struct bomber_cntrl_ctx **bomber_ctx,
                     struct alien_cntrl_ctx **alien_ctx,
                     struct destroyer_cntrl_ctx **destroyer_ctx) {
  struct enemy_cntrl_ctx *ret =
      (struct enemy_cntrl_ctx *)malloc(sizeof(struct enemy_cntrl_ctx));
  if (ret == NULL)
    return NULL;

  ret->bombers = bomber_ctx;
  ret->aliens = alien_ctx;
  ret->destroyers = destroyer_ctx;

  ret->e_shots_ctx =
      init_enemy_shots_cntrl(ENEMY_CNTRL_DEF_ENT_AMNT, ENEMY_CNTRL_DEF_ENT_AMNT,
                             ENEMY_CNTRL_DEF_ENT_AMNT);
  if (ret->e_shots_ctx == NULL)
    return NULL;

  return ret;
}

int free_enemy_cntrl_ctx(struct enemy_cntrl_ctx *ctx) {
  if (ctx == NULL) {
    return -EXIT_FAILURE;
  }

  if (free_enemy_shots_cntrl(ctx->e_shots_ctx) != EXIT_SUCCESS) {
    return -2;
  }

  free(ctx);
  return EXIT_SUCCESS;
}

int enemy_cntrl_move_right(struct enemy_cntrl_ctx *ctx) {
  struct alien_cntrl_ctx *_actx = *(ctx->aliens);
  struct bomber_cntrl_ctx *_bctx = *(ctx->bombers);

  struct destroyer_cntrl_ctx *_dctx = *(ctx->destroyers);
  int ret;

  for (int i = 0; i < _actx->cnt; i++) {
    if (_actx->aliens[i].get_alive()) {

      if (_actx->aliens[i].get_x() >= COLS - 3) {
        ret = EXIT_FAILURE;
        goto ret;
      }

      if (_actx->aliens[i].mv_r() != EXIT_SUCCESS) {
        ret = EXIT_FAILURE;
        goto ret;
      }
    }
  }

  for (int i = 0; i < _bctx->cnt; i++) {
    if (_bctx->bomber[i].get_alive()) {

      if (_bctx->bomber[i].get_x() >= COLS - 3) {
        ret = EXIT_FAILURE;
        goto ret;
      }

      if (_bctx->bomber[i].mv_r() != EXIT_SUCCESS) {
        ret = EXIT_FAILURE;
        goto ret;
      }
    }
  }

  for (int i = 0; i < _dctx->cnt; i++) {
    if (_dctx->destroyers[i].get_alive()) {

      if (_dctx->destroyers[i].get_x() >= COLS - 3) {
        ret = EXIT_FAILURE;
        goto ret;
      }

      if (_dctx->destroyers[i].mv_r() != EXIT_SUCCESS) {
        ret = EXIT_FAILURE;
        goto ret;
      }
    }
  }

  ret = EXIT_SUCCESS;

ret:
  return ret;
}

int enemy_cntrl_move_left(struct enemy_cntrl_ctx *ctx) {
  struct alien_cntrl_ctx *_actx = *(ctx->aliens);
  struct bomber_cntrl_ctx *_bctx = *(ctx->bombers);

  struct destroyer_cntrl_ctx *_dctx = *(ctx->destroyers);
  int ret;

  for (int i = 0; i < _actx->cnt; i++) {
    if (_actx->aliens[i].get_alive()) {

      if (_actx->aliens[i].get_x() <= 3) {
        ret = EXIT_FAILURE;
        goto ret;
      }

      if (_actx->aliens[i].mv_l() != EXIT_SUCCESS) {
        ret = EXIT_FAILURE;
        goto ret;
      }
    }
  }

  for (int i = 0; i < _bctx->cnt; i++) {
    if (_bctx->bomber[i].get_alive()) {

      if (_bctx->bomber[i].get_x() <= 3) {
        ret = EXIT_FAILURE;
        goto ret;
      }

      if (_bctx->bomber[i].mv_l() != EXIT_SUCCESS) {
        ret = EXIT_FAILURE;
        goto ret;
      }
    }
  }

  for (int i = 0; i < _dctx->cnt; i++) {
    if (_dctx->destroyers[i].get_alive()) {

      if (_dctx->destroyers[i].get_x() <= 3) {
        ret = EXIT_FAILURE;
        goto ret;
      }

      if (_dctx->destroyers[i].mv_l() != EXIT_SUCCESS) {
        ret = EXIT_FAILURE;
        goto ret;
      }
    }
  }

  ret = EXIT_SUCCESS;

ret:
  return ret;
}

int enemy_cntrl_move_down(struct enemy_cntrl_ctx *ctx) {
  struct alien_cntrl_ctx *_actx = *(ctx->aliens);
  struct bomber_cntrl_ctx *_bctx = *(ctx->bombers);

  struct destroyer_cntrl_ctx *_dctx = *(ctx->destroyers);
  int ret;

  for (int i = 0; i < _dctx->cnt; i++) {
    if (_dctx->destroyers[i].get_alive()) {

      if (_dctx->destroyers[i].get_y() >= PWALL_CNTRL_SPWAN_HEIGHT) {
        ret = -2;
        goto ret;
      }

      if (_dctx->destroyers[i].mv_d() != EXIT_SUCCESS) {
        ret = EXIT_FAILURE;
        goto ret;
      }
    }
  }

  for (int i = 0; i < _bctx->cnt; i++) {
    if (_bctx->bomber[i].get_alive()) {

      if (_bctx->bomber[i].get_y() >= PWALL_CNTRL_SPWAN_HEIGHT) {
        ret = -2;
        goto ret;
      }

      if (_bctx->bomber[i].mv_d() != EXIT_SUCCESS) {
        ret = EXIT_FAILURE;
        goto ret;
      }
    }
  }

  for (int i = 0; i < _actx->cnt; i++) {
    if (_actx->aliens[i].get_alive()) {

      if (_actx->aliens[i].get_y() >= PWALL_CNTRL_SPWAN_HEIGHT) {
        ret = -2;
        goto ret;
      }

      if (_actx->aliens[i].mv_d() != EXIT_SUCCESS) {
        ret = EXIT_FAILURE;
        goto ret;
      }
    }
  }

  ret = EXIT_SUCCESS;

ret:
  return ret;
}

int enemy_cntrl_loop(struct game_cntrl_ctx *ctx, Settings *settings,
                     uint8_t *stop) {
  if (ctx == NULL) {
    return -EXIT_FAILURE;
  }

  struct enemy_cntrl_ctx *_ectx = ctx->enmy_ctx;

  register_t mov = 0;
  register_t ret = 0;

  register_t mov_d = 0;
  register_t pv;

  while (1 && !(*stop)) {
    while (ctx->_game_cntrl.pause) {
      sleep(1);
    }

    mov = __check_move_res(mov, ret, &pv);
    switch (mov) {

    case ENEMY_CNTRL_GO_RIGHT:
      ret = enemy_cntrl_move_right(_ectx);
      break;

    case ENEMY_CNTRL_GO_LEFT:
      ret = enemy_cntrl_move_left(_ectx);
      break;

    case ENEMY_CNTRL_GO_DOWN:
      if (mov_d >= 3) {
        mov_d = 0;

        if (pv == ENEMY_CNTRL_GO_RIGHT) {
          mov = ENEMY_CNTRL_GO_LEFT;
          break;

        } else if (pv == ENEMY_CNTRL_GO_LEFT) {
          mov = ENEMY_CNTRL_GO_RIGHT;
          break;
        }
      }

      ret = enemy_cntrl_move_down(_ectx);
      if (ret == -2) {
        ctx->_game_cntrl.enemy_finish = 1;
        return -2;
      }
      mov_d++;
      break;
    }

    player_shots_move(ctx);
    enemy_shots_move(ctx);

    usleep(settings->get_enemy_speed_fg());
  }

  return EXIT_SUCCESS;
}

int enemy_cntrl_check_hit(struct enemy_cntrl_ctx *ctx,
                          struct score_cntrl_ctx *score_ctx, Shot *shot,
                          uint8_t type) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  if (score_ctx == NULL)
    return -2;

  if (destroyer_cntrl_check_hit(*(ctx->destroyers), score_ctx, shot, type) !=
      EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  if (bomber_cntrl_check_hit(*(ctx->bombers), score_ctx, shot, type) !=
      EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  if (alien_cntrl_check_hit(*(ctx->aliens), score_ctx, shot, type) !=
      EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int enemy_cntrl_check_alives(struct enemy_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  for (int i = 0; i < (*ctx->aliens)->cnt; i++) {
    if ((*ctx->aliens)->aliens[i].get_alive()) {
      return EXIT_SUCCESS;
    }
  }

  for (int i = 0; i < (*ctx->bombers)->cnt; i++) {
    if ((*ctx->bombers)->bomber[i].get_alive()) {
      return EXIT_SUCCESS;
    }
  }

  for (int i = 0; i < (*ctx->destroyers)->cnt; i++) {
    if ((*ctx->destroyers)->destroyers[i].get_alive()) {
      return EXIT_SUCCESS;
    }
  }

  return EXIT_FAILURE;
}
