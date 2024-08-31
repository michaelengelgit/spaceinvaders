#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

#include "types/shot.h"

Shot::Shot(int _x, int _y, char sym) {
  x = _x;
  y = _y;

  ch = sym;
  active = 0;
}

int Shot::draw() {
  x = check_exit_border_x(x, 1);
  if (x == -UTILS_EXIT_ERR) {
    return -EXIT_FAILURE;
  }

  move(y, x);
  addch(ch);

  return EXIT_SUCCESS;
}

int Shot::clean() {
  if (y > 1) {
    move(y - 1, x);
    addch(' ');
  }

  move(y, x);
  addch(' ');

  return EXIT_SUCCESS;
}

int Shot::mv_u() {
  clean();
  y--;

  draw();
  return EXIT_SUCCESS;
}

int Shot::mv_d() {
  clean();
  y++;

  draw();
  return EXIT_SUCCESS;
}

int Shot::set_xy(int _x, int _y) {
  x = _x;
  y = _y;

  return EXIT_SUCCESS;
}

int Shot::set_inactive() {
  active = 0;
  return EXIT_SUCCESS;
}

int Shot::set_active() {
  active = 1;
  return EXIT_SUCCESS;
}

int Shot::get_active() { return active; }

int Shot::get_x() { return x; }
int Shot::get_y() { return y; }
