#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

#include "types/player.h"

Player::Player(int _x, int _y) {
  x = _x;
  y = _y;
}

int Player::draw() {
  x = player_check_exit_border_x(x, 7);
  if (x == -UTILS_EXIT_ERR) {
    return -EXIT_FAILURE;
  }

  move(y, x - 3);
  addstr(""
         "/ooooo\\"
         "");

  move(y - 1, x - 2);
  addstr(""
         "_/^\\_"
         "");

  return EXIT_SUCCESS;
}

int Player::clean() {
  move(y, x - 4);
  addstr("         ");

  move(y - 1, x - 3);
  addstr("        ");

  return EXIT_SUCCESS;
}

int Player::mv_r() {
  clean();

  x++;
  draw();

  return EXIT_SUCCESS;
}

int Player::mv_l() {
  clean();

  x--;
  draw();

  return EXIT_SUCCESS;
}

int Player::mv_d() {
  clean();

  y++;
  draw();

  return EXIT_SUCCESS;
}

int Player::check_hit(int _x, int _y) {

  if ((_x == x - 3 || _x == x - 2 || _x == x - 1 || _x == x || _x == x + 1 ||
       _x == x + 2 || _x == x + 3) &&
      _y == y) {

    return EXIT_FAILURE;
  }

  if ((_x == x - 2 || _x == x - 1 || _x == x || _x == x + 1 || _x == x + 2) &&
      _y == y - 1) {

    return EXIT_FAILURE;

  } else {
    return EXIT_SUCCESS;
  }
}

int Player::get_x() { return x; }

int Player::get_y() { return y; }
