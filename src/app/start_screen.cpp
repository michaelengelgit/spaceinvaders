#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

#include "app/start_screen.h"

int start_screen_loop(int hs) {
  char shs[30];

  clear();
  refresh();

  move((LINES / 2) - 1, ((COLS / 2) + 3) - LEFT_SHIFT);
  addstr("____ ___   ___   _____ ____  ____ _  __ _   __ ___    ___   ____ ___ "
         "  ____");

  move((LINES / 2), ((COLS / 2) + 2) - LEFT_SHIFT);
  addstr("/ __// _ \\ / _ | / ___// __/ /  _// |/ /| | / // _ |  / _ \\ / __// "
         "_ \\ / __/");

  move((LINES / 2) + 1, ((COLS / 2) + 1) - LEFT_SHIFT);
  addstr("_\\ \\ / ___// __ |/ /__ / _/  _/ / /    / | |/ // __ | / // // _/ / "
         ", _/_\\ \\  ");

  move((LINES / 2) + 2, (COLS / 2) - LEFT_SHIFT);
  addstr("/___//_/   /_/ |_|\\___//___/ /___//_/|_/  |___//_/ "
         "|_|/____//___//_/|_|/___/  ");

  move((LINES / 2) + 10, (COLS / 2) - 12);
  addstr("Press SPACE to start the game.");

  move((LINES / 2) + 12, (COLS / 2) - 12);
  addstr("Press m to enter menu.");

  move((LINES / 2) + 14, (COLS / 2) - 12);
  addstr("Press h for help.");

  move((LINES / 2) + 16, (COLS / 2) - 12);
  addstr("Press q to quit.");

  move(0, 1);
  addstr(HIGH_SCORE_TITLE);

  move(0, 14);
  sprintf(shs, "%d", hs);
  addstr(shs);

  move(0, COLS - 78);
  addstr(CONTROL_TITLE);

  refresh();

  while (1) {
    switch (getch()) {

    case KEY_SPACE:
      clear();
      return EXIT_START_GAME;

    case KEY_q:
      clear();
      return EXIT_QUIT_GAME;

    case KEY_h:
      clear();
      return EXIT_HELP_GAME;

    case KEY_m:
      clear();
      return EXIT_MENU_GAME;

    default:
      break;
    }
  }

  return -EXIT_FAILURE;
}
