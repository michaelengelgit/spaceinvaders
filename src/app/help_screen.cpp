#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

#include "app/help_screen.h"

int help_screen_loop() {

  clear();
  refresh();

  move((LINES / 2) - 20, (COLS / 2) - 3);
  addstr("HELP");

  move((LINES / 2) - 4, (COLS / 2) - 11);
  addstr("Press m for menu.");

  move((LINES / 2) - 2, (COLS / 2) - 11);
  addstr("Press p for pause.");

  move(LINES / 2, (COLS / 2) - 11);
  addstr("Press a or left to move left.");

  move((LINES / 2) + 2, (COLS / 2) - 11);
  addstr("Press d or right to move right.");

  move((LINES / 2) + 4, (COLS / 2) - 11);
  addstr("Press enter to shoot.");

  move((LINES / 2) + 6, (COLS / 2) - 11);
  addstr("Press b to bomb.");

  move((LINES / 2) + 8, (COLS / 2) - 11);
  addstr("Press n to nuke.");

  move((LINES / 2) + 20, (COLS / 2) - 3);
  addstr("s = start screen");

  move((LINES / 2) + 22, (COLS / 2) - 3);
  addstr("m = menu");

  move((LINES / 2) + 24, (COLS / 2) - 3);
  addstr("q = quit");

  refresh();
  while (1) {

    switch (getch()) {
    case KEY_q:
      return EXIT_QUIT_GAME;

    case KEY_m:
      return EXIT_MENU_GAME;

    case KEY_s:
      return EXIT_START_MENU;

    default:
      break;
    }
  }

  return -EXIT_FAILURE;
}
