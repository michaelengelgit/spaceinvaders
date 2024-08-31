#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

#include "types/destroyer.h"

Destroyer::Destroyer(int _x, int _y, int _alive) {
  x = _x;
  y = _y;

  alive = _alive;
}

int Destroyer::draw() {
  x = check_exit_border_x(x, 5);
  if (x == -UTILS_EXIT_ERR) {
    return -1;
  }

  move(y - 1, x - 2);
  addstr("\\   /");

  move(y, x - 1);
  addstr("___");

  move(y + 1, x - 1);
  addstr("\\V/");

  return EXIT_SUCCESS;
}

int Destroyer::clean(int off) {
  move(y - off - 1, x - 3);
  addstr("       ");

  move(y - off, x - 2);
  addstr("     ");

  move(y + 1 - off, x - 2);
  addstr("     ");

  return EXIT_SUCCESS;
}

int Destroyer::mv_r() {
  clean(0);

  x++;
  draw();

  return EXIT_SUCCESS;
}

int Destroyer::mv_l() {
  clean(0);

  x--;
  draw();

  return EXIT_SUCCESS;
}

int Destroyer::mv_d() {
  clean(0);
  y++;

  clean(2);
  clean(0);

  draw();
  return EXIT_SUCCESS;
}

int Destroyer::check_hit(int _x, int _y) {

  if ((_x == x - 2 || _x == x - 1 || _x == x || _x == x + 1 || _x == x + 2) &&
      _y == y - 1) {
    return EXIT_FAILURE;
  }

  if ((_x == x - 1 || _x == x || _x == x + 1) && _y == y) {
    return EXIT_FAILURE;
  }

  if ((_x == x - 1 || _x == x || _x == x + 1) && _y == y + 1) {
    return EXIT_FAILURE;
  }

  else {
    return EXIT_SUCCESS;
  }
}

int Destroyer::set_unalive() {
  alive = 0;
  clean(0);

  return EXIT_SUCCESS;
}

int Destroyer::get_x() { return x; }

int Destroyer::get_y() { return y; }

int Destroyer::get_alive() { return alive; }
