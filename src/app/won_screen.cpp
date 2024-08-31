#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

#include "app/won_screen.h"

int won_screen_loop(int s, int l) {
  char ss[30];
  char ls[30];

  clear();
  refresh();

  move((LINES / 2) - 4, ((COLS / 2) + 1) - LEFT_SHIFT_W);
  addstr(" __        ________  __     __  ________  __              _______    "
         "______   __    __  ________        __ ");

  move((LINES / 2) - 3, ((COLS / 2)) - LEFT_SHIFT_W);
  addstr("|  \\      |        \\|  \\   |  \\|        \\|  \\            |     "
         "  \\  /      \\ |  \\  |  \\|        \\      |  \\");

  move((LINES / 2) - 2, ((COLS / 2)) - LEFT_SHIFT_W);
  addstr("| $$      | $$$$$$$$| $$   | $$| $$$$$$$$| $$            | "
         "$$$$$$$\\|  $$$$$$\\| $$\\ | $$| $$$$$$$$      | $$");

  move((LINES / 2) - 1, ((COLS / 2)) - LEFT_SHIFT_W);
  addstr("| $$      | $$__    | $$   | $$| $$__    | $$            | $$  | $$| "
         "$$  | $$| $$$\\| $$| $$__          | $$");

  move((LINES / 2), ((COLS / 2)) - LEFT_SHIFT_W);
  addstr("| $$      | $$  \\    \\$$\\ /  $$| $$  \\   | $$            | $$  | "
         "$$| $$  | $$| $$$$\\ $$| $$  \\         | $$");

  move((LINES / 2) + 1, ((COLS / 2)) - LEFT_SHIFT_W);
  addstr("| $$      | $$$$$     \\$$\\  $$ | $$$$$   | $$            | $$  | "
         "$$| $$  | $$| $$\\$$ $$| $$$$$          \\$$");

  move((LINES / 2) + 2, (COLS / 2) - LEFT_SHIFT_W);
  addstr("| $$_____ | $$_____    \\$$ $$  | $$_____ | $$_____       | $$__/ "
         "$$| $$__/ $$| $$ \\$$$$| $$_____        __ ");

  move((LINES / 2) + 3, (COLS / 2) - LEFT_SHIFT_W);
  addstr("| $$     \\| $$     \\    \\$$$   | $$     \\| $$     \\      | $$   "
         " $$ \\$$    $$| $$  \\$$$| $$     \\      |  \\");

  move((LINES / 2) + 4, ((COLS / 2) + 1) - LEFT_SHIFT_W);
  addstr(" \\$$$$$$$$ \\$$$$$$$$     \\$     \\$$$$$$$$ \\$$$$$$$$       "
         "\\$$$$$$$   \\$$$$$$  \\$$   \\$$ \\$$$$$$$$       \\$$");

  move((LINES / 2) + 10, (COLS / 2) - 8);
  addstr(SCORE_TITLE);

  move((LINES / 2) + 10, (COLS / 2) + 4);
  sprintf(ss, "%d", s);
  addstr(ss);

  move((LINES / 2) + 12, (COLS / 2) - 8);
  addstr(LIVES_TITLE);

  move((LINES / 2) + 12, (COLS / 2) + 4);
  sprintf(ls, "%d", l);
  addstr(ls);

  move((LINES / 2) + 24, (COLS / 2) - 12);
  addstr("Press SPACE to start the next level.");

  move((LINES / 2) + 26, (COLS / 2) - 12);
  addstr("Press q to quit.");

  move(0, COLS - 78);
  addstr("CONTROL: ad OR left right to move || SPACE to shoot || b to bomb || "
         "n to nuke");

  refresh();

  while (1) {
    switch (getch()) {

    case KEY_SPACE:
      return EXIT_WON_GAME;

    case KEY_q:
      return EXIT_QUIT_GAME;

    default:
      break;
    }
  }

  return -EXIT_FAILURE;
}
