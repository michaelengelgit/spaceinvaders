#include <unistd.h>

#include "core/game/game_cntrl.h"
#include "core/utils.h"

#include "core/game/shots_cntrl.h"

int __player_shot_set_d_shot(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  Shot *d_shot = NULL;
  if (ctx->shot_dta.shots > 0) {

    for (int i = 0; i < ctx->player_ctx->shots_ctx->d_cnt; i++) {

      if (ctx->player_ctx->shots_ctx->d_shots[i].get_active() == 0) {
        d_shot = &(ctx->player_ctx->shots_ctx->d_shots[i]);
        break;
      }
    }

    d_shot->set_active();
    d_shot->set_xy(ctx->player_ctx->player.get_x(),
                   ctx->player_ctx->player.get_y() - 2);

    d_shot->draw();
    ctx->shot_dta.shots--;

    score_cntrl_update_shot(ctx->score_ctx);
  }

  return EXIT_SUCCESS;
}

int __enemy_shot_set_d_shot(struct game_cntrl_ctx *ctx, Destroyer *destroyer) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  Shot *d_shot = NULL;
  for (int i = 0; i < ctx->enmy_ctx->e_shots_ctx->d_cnt; i++) {

    if (ctx->enmy_ctx->e_shots_ctx->d_shots[i].get_active() == 0) {
      d_shot = &(ctx->enmy_ctx->e_shots_ctx->d_shots[i]);
      break;
    }
  }

  d_shot->set_active();
  d_shot->set_xy(destroyer->get_x(), destroyer->get_y() + 2);

  d_shot->draw();
  return EXIT_SUCCESS;
}

int __enemy_shot_set_b_shot(struct game_cntrl_ctx *ctx, Bomber *bomber) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  Shot *b_shot = NULL;
  for (int i = 0; i < ctx->enmy_ctx->e_shots_ctx->b_cnt; i++) {

    if (ctx->enmy_ctx->e_shots_ctx->b_shots[i].get_active() == 0) {
      b_shot = &(ctx->enmy_ctx->e_shots_ctx->b_shots[i]);
      break;
    }
  }

  b_shot->set_active();
  b_shot->set_xy(bomber->get_x(), bomber->get_y() + 2);

  b_shot->draw();
  return EXIT_SUCCESS;
}

int __enemy_shot_set_a_shot(struct game_cntrl_ctx *ctx, Alien *alien) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  Shot *a_shot = NULL;
  for (int i = 0; i < ctx->enmy_ctx->e_shots_ctx->a_cnt; i++) {

    if (ctx->enmy_ctx->e_shots_ctx->a_shots[i].get_active() == 0) {
      a_shot = &(ctx->enmy_ctx->e_shots_ctx->a_shots[i]);
      break;
    }
  }

  a_shot->set_active();
  a_shot->set_xy(alien->get_x(), alien->get_y() + 2);

  a_shot->draw();
  return EXIT_SUCCESS;
}

int __player_shot_set_b_shot(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  Shot *b_shot = NULL;
  if (ctx->shot_dta.bombs > 0) {

    for (int i = 0; i < ctx->player_ctx->shots_ctx->b_cnt; i++) {

      if (ctx->player_ctx->shots_ctx->b_shots[i].get_active() == 0) {
        b_shot = &(ctx->player_ctx->shots_ctx->b_shots[i]);
        break;
      }
    }

    b_shot->set_active();
    b_shot->set_xy(ctx->player_ctx->player.get_x(),
                   ctx->player_ctx->player.get_y() - 2);

    b_shot->draw();
    ctx->shot_dta.bombs--;

    score_cntrl_update_bomb(ctx->score_ctx);
  }

  return EXIT_SUCCESS;
}

int __player_shot_set_n_shot(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  Shot *n_shot = NULL;
  if (ctx->shot_dta.nukes > 0) {

    for (int i = 0; i < ctx->player_ctx->shots_ctx->n_cnt; i++) {

      if (ctx->player_ctx->shots_ctx->n_shots[i].get_active() == 0) {
        n_shot = &(ctx->player_ctx->shots_ctx->n_shots[i]);
        break;
      }
    }

    n_shot->set_active();
    n_shot->set_xy(ctx->player_ctx->player.get_x(),
                   ctx->player_ctx->player.get_y() - 2);

    n_shot->draw();
    ctx->shot_dta.nukes--;

    score_cntrl_update_nuke(ctx->score_ctx);
  }

  return EXIT_SUCCESS;
}

int __alien_gen_shots(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  uint8_t num_shots = gen_r_nm(1, ctx->aliens_ctx->cnt);
  for (int i = 0; i < num_shots; i++) {

    uint8_t alien_n = gen_r_nm(0, ctx->aliens_ctx->cnt - 1);
    if (ctx->aliens_ctx->aliens[alien_n].get_alive()) {

      __enemy_shot_set_a_shot(ctx, &(ctx->aliens_ctx->aliens[alien_n]));
    }
  }

  return EXIT_SUCCESS;
}

int __bomber_gen_shots(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  uint8_t num_shots = gen_r_nm(1, ctx->bomber_ctx->cnt);
  for (int i = 0; i < num_shots; i++) {

    uint8_t bomber_n = gen_r_nm(0, ctx->bomber_ctx->cnt - 1);
    if (ctx->bomber_ctx->bomber[bomber_n].get_alive()) {

      __enemy_shot_set_b_shot(ctx, &(ctx->bomber_ctx->bomber[bomber_n]));
    }
  }

  return EXIT_SUCCESS;
}

int __destroyer_gen_shots(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  uint8_t num_shots = gen_r_nm(1, ctx->destroyers_ctx->cnt);
  for (int i = 0; i < num_shots; i++) {

    uint8_t destroyer_n = gen_r_nm(0, ctx->destroyers_ctx->cnt - 1);
    if (ctx->destroyers_ctx->destroyers[destroyer_n].get_alive()) {

      __enemy_shot_set_d_shot(ctx,
                              &(ctx->destroyers_ctx->destroyers[destroyer_n]));
    }
  }

  return EXIT_SUCCESS;
}

int __shot_clean(Shot *shot) {
  if (shot == NULL)
    return -EXIT_FAILURE;

  shot->set_inactive();
  shot->clean();

  return EXIT_SUCCESS;
}

int __player_shots_check_border(Shot *shot) {
  if (shot->get_y() <= 1) {
    __shot_clean(shot);

    return EXIT_FAILURE;
  }

  else {
    return EXIT_SUCCESS;
  }
}

int __enemy_shots_check_border(Shot *shot) {
  if (shot->get_y() >= LINES - 1) {
    __shot_clean(shot);

    return EXIT_FAILURE;
  }

  else {
    return EXIT_SUCCESS;
  }
}

int __shots_check_pwall(struct pwall_cntrl_ctx *ctx, Shot *shot) {
  if (pwall_cntrl_check_hit(ctx, shot) == EXIT_FAILURE) {
    __shot_clean(shot);

    return EXIT_FAILURE;
  }

  else {
    return EXIT_SUCCESS;
  }
}

int __player_shots_check_enemy(struct enemy_cntrl_ctx *ctx,
                               struct score_cntrl_ctx *score_ctx, Shot *shot,
                               uint8_t type) {

  if (enemy_cntrl_check_hit(ctx, score_ctx, shot, type) == EXIT_FAILURE) {
    __shot_clean(shot);
    return EXIT_FAILURE;
  }

  else {
    return EXIT_SUCCESS;
  }
}

int __enemy_shots_check_player(struct player_cntrl_ctx *p_ctx,
                               struct score_cntrl_ctx *score_ctx, Shot *shot) {

  if (player_cntrl_check_hit(p_ctx, score_ctx, shot) == EXIT_FAILURE) {
    __shot_clean(shot);
    return EXIT_FAILURE;
  }

  else {
    return EXIT_SUCCESS;
  }
}

struct player_shots_cntrl_ctx *init_player_shots_cntrl(int d_cnt, int b_cnt,
                                                       int n_cnt) {
  struct player_shots_cntrl_ctx *ctx = (struct player_shots_cntrl_ctx *)malloc(
      sizeof(struct player_shots_cntrl_ctx));
  if (ctx == NULL) {
    return NULL;
  }

  ctx->d_cnt = d_cnt;
  ctx->b_cnt = b_cnt;
  ctx->n_cnt = n_cnt;

  ctx->d_shots = (Shot *)malloc(sizeof(Shot) * d_cnt);
  if (ctx->d_shots == NULL)
    return NULL;

  ctx->b_shots = (Shot *)malloc(sizeof(Shot) * b_cnt);
  if (ctx->b_shots == NULL)
    return NULL;

  ctx->n_shots = (Shot *)malloc(sizeof(Shot) * n_cnt);
  if (ctx->n_shots == NULL)
    return NULL;

  for (int i = 0; i < d_cnt; i++) {
    ctx->d_shots[i] = Shot(0, 0, SHOT_CNTRL_DEF_SHOT_SYM);
  }

  for (int i = 0; i < b_cnt; i++) {
    ctx->b_shots[i] = Shot(0, 0, SHOT_CNTRL_DEF_BOMB_SYM);
  }

  for (int i = 0; i < n_cnt; i++) {
    ctx->n_shots[i] = Shot(0, 0, SHOT_CNTRL_DEF_NUKE_SYM);
  }

  return ctx;
}

struct enemy_shots_cntrl_ctx *init_enemy_shots_cntrl(int a_cnt, int b_cnt,
                                                     int d_cnt) {
  struct enemy_shots_cntrl_ctx *ctx = (struct enemy_shots_cntrl_ctx *)malloc(
      sizeof(struct enemy_shots_cntrl_ctx));
  if (ctx == NULL) {
    return NULL;
  }

  ctx->a_cnt = a_cnt;
  ctx->b_cnt = b_cnt;
  ctx->d_cnt = d_cnt;

  ctx->a_shots = (Shot *)malloc(sizeof(Shot) * a_cnt);
  if (ctx->a_shots == NULL)
    return NULL;

  ctx->b_shots = (Shot *)malloc(sizeof(Shot) * b_cnt);
  if (ctx->b_shots == NULL)
    return NULL;

  ctx->d_shots = (Shot *)malloc(sizeof(Shot) * d_cnt);
  if (ctx->d_shots == NULL)
    return NULL;

  for (int i = 0; i < a_cnt; i++) {
    ctx->a_shots[i] = Shot(0, 0, SHOT_CNTRL_DEF_ALIEN_SHOT_SYM);
  }

  for (int i = 0; i < b_cnt; i++) {
    ctx->b_shots[i] = Shot(0, 0, SHOT_CNTRL_DEF_BOMBER_SHOT_SYM);
  }

  for (int i = 0; i < d_cnt; i++) {
    ctx->d_shots[i] = Shot(0, 0, SHOT_CNTRL_DEF_DESTROYER_SHOT_SYM);
  }

  return ctx;
}

int free_player_shots_cntrl(struct player_shots_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  free(ctx->d_shots);
  free(ctx->b_shots);

  free(ctx->n_shots);
  free(ctx);

  return EXIT_SUCCESS;
}

int free_enemy_shots_cntrl(struct enemy_shots_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  free(ctx->a_shots);
  free(ctx->b_shots);

  free(ctx->d_shots);
  free(ctx);

  return EXIT_SUCCESS;
}

int player_shot_set(struct game_cntrl_ctx *ctx, uint8_t type) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  switch (type) {
  case SHOT_CNTRL_DEFAULT_SHOT:
    __player_shot_set_d_shot(ctx);
    break;

  case SHOT_CNTRL_BOMB_SHOT:
    __player_shot_set_b_shot(ctx);
    break;

  case SHOT_CNTRL_NUKE_SHOT:
    __player_shot_set_n_shot(ctx);
    break;

  default:
    return -2;
  }

  return EXIT_SUCCESS;
}
int enemy_shots_set(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  uint8_t type =
      gen_r_nm(SHOT_CNTRL_ALIEN_SHOT, SHOT_CNTRL_ALIEN_BOMBER_DESTROYER_SHOT);
  switch (type) {

  case SHOT_CNTRL_ALIEN_SHOT:
    __alien_gen_shots(ctx);
    break;

  case SHOT_CNTRL_BOMBER_SHOT:
    __bomber_gen_shots(ctx);
    break;

  case SHOT_CNTRL_DESTROYER_SHOT:
    __destroyer_gen_shots(ctx);
    break;

  case SHOT_CNTRL_ALIEN_BOMBER_SHOT:
    __alien_gen_shots(ctx);
    __bomber_gen_shots(ctx);
    break;

  case SHOT_CNTRL_ALIEN_DESTROYER_SHOT:
    __alien_gen_shots(ctx);
    __destroyer_gen_shots(ctx);
    break;

  case SHOT_CNTRL_BOMBER_DESTROYER_SHOT:
    __bomber_gen_shots(ctx);
    __destroyer_gen_shots(ctx);
    break;

  case SHOT_CNTRL_ALIEN_BOMBER_DESTROYER_SHOT:
    __alien_gen_shots(ctx);
    __bomber_gen_shots(ctx);
    __destroyer_gen_shots(ctx);
    break;

  default:
    return -2;
  }

  return EXIT_SUCCESS;
}

int player_shots_move(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  struct player_shots_cntrl_ctx *__ps_ctx = ctx->player_ctx->shots_ctx;
  for (int i = 0; i < __ps_ctx->d_cnt; i++) {

    if (__ps_ctx->d_shots[i].get_active() == 1) {

      if (__shots_check_pwall(ctx->pwalls_ctx, &(__ps_ctx->d_shots[i])) !=
          EXIT_FAILURE) {

        if (__player_shots_check_enemy(
                ctx->enmy_ctx, ctx->score_ctx, &(__ps_ctx->d_shots[i]),
                SHOT_CNTRL_DEFAULT_SHOT) != EXIT_FAILURE) {

          if (__player_shots_check_border(&(__ps_ctx->d_shots[i])) !=
              EXIT_FAILURE) {

            __ps_ctx->d_shots[i].mv_u();
          }
        }
      }
    }
  }

  for (int i = 0; i < __ps_ctx->b_cnt; i++) {

    if (__ps_ctx->b_shots[i].get_active() == 1) {

      if (__shots_check_pwall(ctx->pwalls_ctx, &(__ps_ctx->b_shots[i])) !=
          EXIT_FAILURE) {

        if (__player_shots_check_enemy(ctx->enmy_ctx, ctx->score_ctx,
                                       &(__ps_ctx->b_shots[i]),
                                       SHOT_CNTRL_BOMB_SHOT) != EXIT_FAILURE) {

          if (__player_shots_check_border(&(__ps_ctx->b_shots[i])) !=
              EXIT_FAILURE) {

            __ps_ctx->b_shots[i].mv_u();
          }
        }
      }
    }
  }

  for (int i = 0; i < __ps_ctx->n_cnt; i++) {

    if (__ps_ctx->n_shots[i].get_active() == 1) {

      if (__shots_check_pwall(ctx->pwalls_ctx, &(__ps_ctx->n_shots[i])) !=
          EXIT_FAILURE) {

        if (__player_shots_check_enemy(ctx->enmy_ctx, ctx->score_ctx,
                                       &(__ps_ctx->n_shots[i]),
                                       SHOT_CNTRL_NUKE_SHOT) != EXIT_FAILURE) {

          if (__player_shots_check_border(&(__ps_ctx->n_shots[i])) !=
              EXIT_FAILURE) {

            __ps_ctx->n_shots[i].mv_u();
          }
        }
      }
    }
  }

  return EXIT_SUCCESS;
}

int enemy_shots_move(struct game_cntrl_ctx *ctx) {
  if (ctx == NULL)
    return -EXIT_FAILURE;

  struct enemy_shots_cntrl_ctx *__es_ctx = ctx->enmy_ctx->e_shots_ctx;
  for (int i = 0; i < __es_ctx->d_cnt; i++) {

    if (__es_ctx->d_shots[i].get_active() == 1) {

      if (__shots_check_pwall(ctx->pwalls_ctx, &(__es_ctx->d_shots[i])) !=
          EXIT_FAILURE) {

        if (__enemy_shots_check_player(ctx->player_ctx, ctx->score_ctx,
                                       &(__es_ctx->d_shots[i])) !=
            EXIT_FAILURE) {

          if (__enemy_shots_check_border(&(__es_ctx->d_shots[i])) !=
              EXIT_FAILURE) {

            __es_ctx->d_shots[i].mv_d();
          }
        }
      }
    }
  }

  for (int i = 0; i < __es_ctx->b_cnt; i++) {

    if (__es_ctx->b_shots[i].get_active() == 1) {

      if (__shots_check_pwall(ctx->pwalls_ctx, &(__es_ctx->b_shots[i])) !=
          EXIT_FAILURE) {

        if (__enemy_shots_check_player(ctx->player_ctx, ctx->score_ctx,
                                       &(__es_ctx->b_shots[i])) !=
            EXIT_FAILURE) {

          if (__enemy_shots_check_border(&(__es_ctx->b_shots[i])) !=
              EXIT_FAILURE) {

            __es_ctx->b_shots[i].mv_d();
          }
        }
      }
    }
  }

  for (int i = 0; i < __es_ctx->a_cnt; i++) {

    if (__es_ctx->a_shots[i].get_active() == 1) {

      if (__shots_check_pwall(ctx->pwalls_ctx, &(__es_ctx->a_shots[i])) !=
          EXIT_FAILURE) {

        if (__enemy_shots_check_player(ctx->player_ctx, ctx->score_ctx,
                                       &(__es_ctx->a_shots[i])) !=
            EXIT_FAILURE) {

          if (__enemy_shots_check_border(&(__es_ctx->a_shots[i])) !=
              EXIT_FAILURE) {

            __es_ctx->a_shots[i].mv_d();
          }
        }
      }
    }
  }

  return EXIT_SUCCESS;
}

int shots_cntrl_update_shots(struct game_cntrl_ctx *ctx, Settings *settings,
                             uint8_t *stop) {
  while (1 && !(*stop)) {
    sleep(settings->get_shot_cooldown());

    while (ctx->_game_cntrl.pause) {
      sleep(1);
    }

    if (ctx->shot_dta.shots < 3) {
      ctx->shot_dta.shots++;
      score_cntrl_update_shot(ctx->score_ctx);
    }

    if (gen_r_nm(0, settings->get_bomb_chance() + 1) == 1) {
      if (ctx->shot_dta.bombs < 3) {

        ctx->shot_dta.bombs++;
        score_cntrl_update_bomb(ctx->score_ctx);
      }
    }

    if (gen_r_nm(0, settings->get_nuke_chance() + 2) == 1) {
      if (ctx->shot_dta.nukes < 3) {

        ctx->shot_dta.nukes++;
        score_cntrl_update_nuke(ctx->score_ctx);
      }
    }
  }

  return EXIT_SUCCESS;
}

int shots_cntrl_enemy_shot_loop(struct game_cntrl_ctx *ctx, uint8_t *stop) {
  while (1 && !(*stop)) {

    while (ctx->_game_cntrl.pause) {
      sleep(1);
    }

    enemy_shots_set(ctx);
    sleep(gen_r_nm(0, 3));
  }

  return EXIT_SUCCESS;
}
