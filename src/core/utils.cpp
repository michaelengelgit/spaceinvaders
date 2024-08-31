#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

int __init_scr() {
  initscr();
  clear();

  noecho();
  cbreak();

  nodelay(stdscr, 1);
  keypad(stdscr, 1);

  curs_set(FALSE);

  return EXIT_SUCCESS;
}

int __free_scr() {
  erase();
  refresh();

  endwin();

  return EXIT_SUCCESS;
}

int check_exit_border_x(int x, int l) {
  int ret = -UTILS_EXIT_ERR;
  int rad = 0;

  if (l % UTILS_NUM_EV != UTILS_ONE_OFFSET) {
    goto ret;
  }

  else {
    rad = (l - UTILS_ONE_OFFSET) / UTILS_NUM_EV;
  }

  if (x <= rad) {
    goto ret;
  }

  else if (x > COLS - (rad + UTILS_ONE_OFFSET)) {
    goto ret;
  }

  else {
    ret = x;
  }

ret:
  return ret;
}

int player_check_exit_border_x(int x, int l) {
  int ret = -UTILS_EXIT_ERR;
  int rad = 0;

  if (l % UTILS_NUM_EV != UTILS_ONE_OFFSET) {
    goto ret;
  }

  else {
    rad = (l - UTILS_ONE_OFFSET) / UTILS_NUM_EV;
  }

  if (x <= rad) {
    ret = rad;
    goto ret;
  }

  else if (x > COLS - (rad + UTILS_ONE_OFFSET)) {
    ret = COLS - (rad + UTILS_ONE_OFFSET);
    goto ret;
  }

  else {
    ret = x;
  }

ret:
  return ret;
}

int calc_cnt(int x, int ent_len, int min_gap_len) {
  if (x < ent_len) {
    return -EXIT_FAILURE;
  }

  if (x < (min_gap_len * ent_len) * 2) {
    return -2;
  }

  int _nx = (x - (min_gap_len * ent_len * 2));
  int tmp = _nx % (ent_len * 3);

  if (tmp != 0) {

    int nx = _nx - tmp;
    return (nx / (ent_len * 3));

  } else {
    return _nx / (ent_len * 3);
  }

  return -3;
}

int gen_r_nm(uint8_t min, uint8_t max) {
  return rand() % (max - min + 1) + min;
}
