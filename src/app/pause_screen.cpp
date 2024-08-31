#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

#include "app/pause_screen.h"

int pause_screen_loop() {
  clear();
  refresh();

  move((LINES / 2) - 10, ((COLS / 2) + 3) - LEFT_SHIFT_P);
  addstr("____ ___   ___   _____ ____  ____ _  __ _   __ ___    ___   ____ ___ "
         "  ____");

  move((LINES / 2) - 9, ((COLS / 2) + 2) - LEFT_SHIFT_P);
  addstr("/ __// _ \\ / _ | / ___// __/ /  _// |/ /| | / // _ |  / _ \\ / __// "
         "_ \\ / __/");

  move((LINES / 2) - 8, ((COLS / 2) + 1) - LEFT_SHIFT_P);
  addstr("_\\ \\ / ___// __ |/ /__ / _/  _/ / /    / | |/ // __ | / // // _/ / "
         ", _/_\\ \\  ");

  move((LINES / 2) - 7, (COLS / 2) - LEFT_SHIFT_P);
  addstr("/___//_/   /_/ |_|\\___//___/ /___//_/|_/  |___//_/ "
         "|_|/____//___//_/|_|/___/  ");

  move((LINES / 2), (COLS / 2) - 3);
  addstr("[PAUSE]");

  move((LINES / 2) + 4, (COLS / 2) - 8);
  addstr("SPACE = continue game");

  move((LINES / 2) + 6, (COLS / 2) - 3);
  addstr("q = quit");

  refresh();

  while (1) {
    switch (getch()) {

    case KEY_q:
      return EXIT_QUIT_GAME;

    case KEY_SPACE:
      return EXIT_CONTINUE_GAME;

    default:
      break;
    }
  }

  return -EXIT_FAILURE;
}
