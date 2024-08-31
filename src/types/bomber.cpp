#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

#include "types/bomber.h"

Bomber::Bomber(int _x, int _y, int _alive) {
  x = _x;
  y = _y;

  alive = _alive;
}

int Bomber::draw() {
  x = check_exit_border_x(x, 5);
  if (x == -UTILS_EXIT_ERR) {
    return -EXIT_FAILURE;
  }

  move(y, x - 1);
  addstr("|~|");

  move(y - 1, x - 2);
  addstr("/P^P\\");

  return EXIT_SUCCESS;
}

int Bomber::clean(int off) {
  move(y - off, x - 2);
  addstr("     ");

  move(y - off - 1, x - 3);
  addstr("       ");

  return EXIT_SUCCESS;
}

int Bomber::mv_r() {
  clean(0);

  x++;
  draw();

  return EXIT_SUCCESS;
}

int Bomber::mv_l() {
  clean(0);

  x--;
  draw();

  return EXIT_SUCCESS;
}

int Bomber::mv_d() {
  clean(0);
  y++;

  clean(2);
  clean(0);

  draw();
  return EXIT_SUCCESS;
}

int Bomber::check_hit(int _x, int _y) {

  if ((_x == x - 2 || _x == x - 1 || _x == x || _x == x + 1 || _x == x + 2) &&
      _y == y - 1) {
    return EXIT_FAILURE;
  }

  if ((_x == x - 1 || _x == x || _x == x + 1) && _y == y) {
    return EXIT_FAILURE;
  }

  else {
    return EXIT_SUCCESS;
  }
}

int Bomber::set_unalive() {
  alive = 0;
  clean(0);

  return EXIT_SUCCESS;
}

int Bomber::get_x() { return x; }

int Bomber::get_y() { return y; }

int Bomber::get_alive() { return alive; }
