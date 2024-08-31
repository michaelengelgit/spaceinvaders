#include <ncurses.h>
#include <unistd.h>

#include "core/utils.h"
#include "io/toml.h"

#include "app/menu_screen.h"

int __print_ok() {
  move((LINES / 2) - 11, (COLS / 2) - 1);
  addstr("[OK]");

  refresh();
  sleep(1);

  return EXIT_SUCCESS;
}

int __change_shot_cooldown(Settings *settings) {
  clear();
  refresh();

  move((LINES / 2) - 20, (COLS / 2) - 10);
  addstr("Change setting shot cooldown");

  move((LINES / 2) - 15, (COLS / 2) - 10);
  addstr("Current value: ");

  move((LINES / 2) - 15, (COLS / 2) + 13);
  addstr(std::to_string(settings->get_shot_cooldown()).c_str());

  move((LINES / 2) - 13, (COLS / 2) - 10);
  addstr("Options available: 0, ..., 100000 and press enter to finish.");

  refresh();

  int num = 0;
  int ch;
  std::string inp;

  while (1) {
    ch = getch();

    if (ch >= '0' && ch <= '9') {
      inp += ch;
    }

    else if (ch == '\n' || ch == '\r') {
      break;
    }

    else if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {

      if (!inp.empty()) {
        inp.pop_back();
      }
    }

    refresh();
  }

  if (!inp.empty()) {
    num = std::stoi(inp);
  }

  if (num < 0 || num > SETTINGS_MAX_SHOT_COOLDOWN) {
    return EXIT_FAILURE;
  }

  settings->change_shot_cooldown(num);

  __print_ok();
  return EXIT_SUCCESS;
}

int __change_enemy_speed(Settings *settings) {
  clear();
  refresh();

  move((LINES / 2) - 20, (COLS / 2) - 10);
  addstr("Change setting  enemy speed");

  move((LINES / 2) - 15, (COLS / 2) - 10);
  addstr("Current value: ");

  move((LINES / 2) - 15, (COLS / 2) + 13);
  addstr(settings->get_enemy_speed_string().c_str());

  move((LINES / 2) - 13, (COLS / 2) - 10);
  addstr("Options available: slow, normal, fast (s, n, f)");

  refresh();

beg:

  int inp = wgetch(stdscr);
  switch (inp) {

  case KEY_s:
    settings->change_enemy_speed(0);

    __print_ok();
    break;

  case KEY_n:
    settings->change_enemy_speed(1);

    __print_ok();
    break;

  case KEY_f:
    settings->change_enemy_speed(2);

    __print_ok();
    break;

  default:
    goto beg;
  }

  return EXIT_SUCCESS;
}

int __change_bomb_chance(Settings *settings) {
  clear();
  refresh();

  move((LINES / 2) - 20, (COLS / 2) - 10);
  addstr("Change setting bomb chance");

  move((LINES / 2) - 15, (COLS / 2) - 10);
  addstr("Current value: ");

  move((LINES / 2) - 15, (COLS / 2) + 13);
  addstr(settings->get_bomb_chance_string().c_str());

  move((LINES / 2) - 13, (COLS / 2) - 10);
  addstr("Options available: low , normal, high (l, n, h)");

  refresh();

beg:

  int inp = wgetch(stdscr);
  switch (inp) {

  case KEY_l:
    settings->change_bomb_chance(0);

    __print_ok();
    break;

  case KEY_n:
    settings->change_bomb_chance(1);

    __print_ok();
    break;

  case KEY_h:
    settings->change_bomb_chance(2);

    __print_ok();
    break;

  default:
    goto beg;
  }

  return EXIT_SUCCESS;
}

int __change_nuke_chance(Settings *settings) {
  clear();
  refresh();

  move((LINES / 2) - 20, (COLS / 2) - 10);
  addstr("Change setting nuke chance");

  move((LINES / 2) - 15, (COLS / 2) - 10);
  addstr("Current value: ");

  move((LINES / 2) - 15, (COLS / 2) + 13);
  addstr(settings->get_nuke_chance_string());

  move((LINES / 2) - 13, (COLS / 2) - 10);
  addstr("Options available: low , normal, high (l, n, h)");

  refresh();

beg:

  int inp = wgetch(stdscr);
  switch (inp) {

  case KEY_l:
    settings->change_nuke_chance(0);

    __print_ok();
    break;

  case KEY_n:
    settings->change_nuke_chance(1);

    __print_ok();
    break;

  case KEY_h:
    settings->change_nuke_chance(2);

    __print_ok();
    break;

  default:
    goto beg;
  }

  return EXIT_SUCCESS;
}

int __change_pwall_cnt(Settings *settings) {
  clear();
  refresh();

  move((LINES / 2) - 20, (COLS / 2) - 10);
  addstr("Change setting pwall amount ");

  move((LINES / 2) - 15, (COLS / 2) - 10);
  addstr("Current value: ");

  move((LINES / 2) - 15, (COLS / 2) + 13);
  addstr(std::to_string(settings->get_pwall_cnt()).c_str());

  move((LINES / 2) - 13, (COLS / 2) - 10);
  addstr("Options available: 0, ..., 6 and press enter to finish.");

  refresh();

  int num = 0;
  int ch;
  std::string inp;

  while (1) {

    ch = getch();

    if (ch >= '0' && ch <= '9') {
      inp += ch;
    }

    else if (ch == '\n' || ch == '\r') {
      break;
    }

    else if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {

      if (!inp.empty()) {
        inp.pop_back();
      }
    }

    refresh();
  }

  if (!inp.empty()) {
    num = std::stoi(inp);
  }

  if (num < 0 || num > SETTINGS_MAX_PWALL_CNT) {
    return EXIT_FAILURE;
  }

  settings->change_pwall_cnt(num);

  __print_ok();
  return EXIT_SUCCESS;
}

int __change_pwall_live(Settings *settings) {
  clear();
  refresh();

  move((LINES / 2) - 20, (COLS / 2) - 10);
  addstr("Change setting pwall live");

  move((LINES / 2) - 15, (COLS / 2) - 10);
  addstr("Current value: ");

  move((LINES / 2) - 15, (COLS / 2) + 13);
  addstr(std::to_string(settings->get_pwall_live()).c_str());

  move((LINES / 2) - 13, (COLS / 2) - 10);
  addstr("Options available: 0, ..., 50 and press enter to finish.");

  refresh();

  int num = 0;
  int ch;
  std::string inp;

  while (1) {

    ch = getch();

    if (ch >= '0' && ch <= '9') {
      inp += ch;
    }

    else if (ch == '\n' || ch == '\r') {
      break;
    }

    else if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {

      if (!inp.empty()) {
        inp.pop_back();
      }
    }

    refresh();
  }

  if (!inp.empty()) {
    num = std::stoi(inp);
  }

  if (num < 0 || num > SETTINGS_MAX_PWALL_LIVE) {
    return EXIT_FAILURE;
  }

  settings->change_pwall_live(num);

  __print_ok();
  return EXIT_SUCCESS;
}

int menu_screen_loop(Settings *settings) {
  clear();
  refresh();

  move((LINES / 2) - 20, (COLS / 2) - 3);
  addstr("MENU");

  move((LINES / 2) - 4, (COLS / 2) - 11);
  addstr("A) Change shot cooldown.");

  move((LINES / 2) - 2, (COLS / 2) - 11);
  addstr("B) Change enemy speed.");

  move(LINES / 2, (COLS / 2) - 11);
  addstr("C) Change bomb chance.");

  move((LINES / 2) + 2, (COLS / 2) - 11);
  addstr("D) Change nuke chance");

  move((LINES / 2) + 4, (COLS / 2) - 11);
  addstr("E) Change pwall amount.");

  move((LINES / 2) + 6, (COLS / 2) - 11);
  addstr("F) Change pwall live.");

  move((LINES / 2) + 12, (COLS / 2) - 11);
  addstr("YOUR CHOICE (A, ..., F, s, q): ");

  move((LINES / 2) + 20, (COLS / 2) - 11);
  addstr("s = start screen");

  move((LINES / 2) + 22, (COLS / 2) - 11);
  addstr("q = quit");

  refresh();

beg:

  int inp = wgetch(stdscr);
  switch (inp) {

  case KEY_q:
    return EXIT_QUIT_GAME;

  case KEY_s:
    return EXIT_START_MENU;

  case _KEY_A:
    __change_shot_cooldown(settings);

    toml_write_settings(settings);
    break;

  case _KEY_B:
    __change_enemy_speed(settings);

    toml_write_settings(settings);
    break;

  case _KEY_C:
    __change_bomb_chance(settings);

    toml_write_settings(settings);
    break;

  case _KEY_D:
    __change_nuke_chance(settings);

    toml_write_settings(settings);
    break;

  case _KEY_E:
    __change_pwall_cnt(settings);

    toml_write_settings(settings);
    break;

  case _KEY_F:
    __change_pwall_live(settings);

    toml_write_settings(settings);
    break;

  default:
    goto beg;
  }

  return EXIT_START_MENU;
}
