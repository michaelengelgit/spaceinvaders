#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

#include "types/pwall.h"

Pwall::Pwall(int _x, int _y, int _live) {
  x = _x;
  y = _y;

  live = _live;
}

int Pwall::draw() {
  char tstr[2];

  x = check_exit_border_x(x, 1);
  if (x == -UTILS_EXIT_ERR) {
    return -EXIT_FAILURE;
  }

  move(y, x - 3);
  addstr("||     ||");

  sprintf(tstr, "%d", live);
  move(y, x + 1);
  addstr(tstr);

  move(y - 1, x - 2);
  addstr("=======");

  return EXIT_SUCCESS;
}

int Pwall::clean() {
  move(y, x - 3);
  addstr("           ");

  move(y - 1, x - 2);
  addstr("       ");

  return EXIT_SUCCESS;
}

int Pwall::d_live() {
  char tstr[2];

  if (live > 0) {
    live--;

    move(y, x + 1);
    addstr("  ");

    move(y, x + 1);
    sprintf(tstr, "%d", live);

    addstr(tstr);

  } else {

    clean();
    return -EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int Pwall::check_hit(int _x, int _y) {
  if ((_x == x || _x == x + 1 || _x == x + 2 || _x == x + 3 || _x == x + 4 ||
       _x == x + 5 || _x == x - 1 || _x == x - 2 || _x == x - 3) &&
      _y == y + 1) {

    return EXIT_FAILURE;
  }

  if ((_x == x || _x == x + 1 || _x == x + 2 || _x == x + 3 || _x == x + 4 ||
       _x == x + 5 || _x == x - 1 || _x == x - 2 || _x == x - 3) &&
      _y == y - 1) {

    return EXIT_FAILURE;
  }

  else {
    return EXIT_SUCCESS;
  }
}

int Pwall::is_alive() {

  if (live == 0) {
    clean();
    return EXIT_SUCCESS;
  }

  else {
    return EXIT_FAILURE;
  }
}
