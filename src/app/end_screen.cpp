#include <cstdlib>
#include <ncurses.h>

#include "core/utils.h"

#include "app/end_screen.h"

int end_screen_loop(int s) {
  char ss[30];

  clear();
  refresh();

  move((LINES / 2) - 2, ((COLS / 2) + 4) - LEFT_SHIFT_E);
  addstr("//   ) )  // | |     /|    //| |     //   / /       //   ) ) ||   / "
         "/ //   / /  //   ) ) ");

  move((LINES / 2) - 1, ((COLS / 2) + 3) - LEFT_SHIFT_E);
  addstr("//        //__| |    //|   // | |    //____         //   / /  ||  / "
         "/ //____    //___/ /  ");

  move((LINES / 2), ((COLS / 2) + 2) - LEFT_SHIFT_E);
  addstr("//  ____  / ___  |   // |  //  | |   / ____         //   / /   || / "
         "/ / ____    / ___ (    ");

  move((LINES / 2) + 1, ((COLS / 2) + 1) - LEFT_SHIFT_E);
  addstr("//    / / //    | |  //  | //   | |  //             //   / /    ||/ "
         "/ //        //   | |    ");

  move((LINES / 2) + 2, (COLS / 2) - LEFT_SHIFT_E);
  addstr("((____/ / //     | | //   |//    | | //____/ /      ((___/ /     |  "
         "/ //____/ / //    | |    ");

  move((LINES / 2) + 10, (COLS / 2) - 12);
  addstr(HIGH_SCORE_TITLE);

  move((LINES / 2) + 10, (COLS / 2) + 2);
  sprintf(ss, "%d", s);
  addstr(ss);

  move((LINES / 2) + 14, (COLS / 2) - 12);
  addstr("Press SPACE to restart the game.");

  move((LINES / 2) + 16, (COLS / 2) - 12);
  addstr("Press m to enter menu.");

  move((LINES / 2) + 18, (COLS / 2) - 12);
  addstr("Press h for help.");

  move((LINES / 2) + 20, (COLS / 2) - 12);
  addstr("Press q to quit.");

  move(0, COLS - 78);
  addstr("CONTROL: ad OR left right to move || SPACE to shoot || b to bomb || "
         "n to nuke");

  refresh();
  while (1) {

    switch (getch()) {
    case KEY_SPACE:
      return EXIT_START_GAME;

    case KEY_q:
      return EXIT_QUIT_GAME;

    case KEY_m:
      return EXIT_MENU_GAME;

    case KEY_h:
      return EXIT_HELP_GAME;

    default:
      break;
    }
  }

  return -EXIT_FAILURE;
}
