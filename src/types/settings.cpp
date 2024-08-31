#include <cstdlib>

#include "types/settings.h"

int __check_string_val(std::string inp) {

  if (inp.compare("slow") == EXIT_SUCCESS) {
    return SETTINGS_ENEMY_SPEED_SLOW;
  }

  else if (inp.compare("low") == EXIT_SUCCESS) {
    return SETTINGS_WEAPON_CHANGE_LOW;
  }

  else if (inp.compare("normal") == EXIT_SUCCESS) {
    return SETTINGS_ENEMY_SPEED_NORMAL;
  }

  else if (inp.compare("fast") == EXIT_SUCCESS) {
    return SETTINGS_ENEMY_SPEED_FAST;
  }

  else if (inp.compare("high") == EXIT_SUCCESS) {
    return SETTINGS_WEAPON_CHANGE_HIGH;
  }

  else {
    return EXIT_FAILURE;
  }
}

int __check_cooldown_val(int val) {
  switch (val) {

  case 0:
    return 0;

  case 1:
    return 1;

  case 2:
    return 2;

  default:
    return DEF_SHOT_COOLDOWN;
  }
}

int __check_pwall_amt_val(int val) {
  if (val > SETTINGS_MAX_PWALL_CNT)
    return DEF_PWALL_AMOUNT;

  else {
    return val;
  }
}

int __check_pwall_live_val(int val) {
  if (val > SETTINGS_MAX_PWALL_LIVE)
    return DEF_PWALL_LIVE;

  else {
    return val;
  }
}

int Settings::check_new_high_score(int new_score) {
  if ((uint32_t )new_score > high_score) {

    high_score = new_score;
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}

Settings::Settings(uint8_t _shot_cooldown, std::string _enemy_speed,
                   std::string _bomb_chance, std::string _nuke_chance,
                   uint8_t _pwall_cnt, uint8_t _pwall_live,
                   uint32_t _high_score) {

  shot_cooldown = __check_cooldown_val(_shot_cooldown);
  enemy_speed = __check_string_val(_enemy_speed);

  bomb_chance = __check_string_val(_bomb_chance);
  nuke_chance = __check_string_val(_nuke_chance);

  pwall_cnt = __check_pwall_amt_val(_pwall_cnt);
  pwall_live = __check_pwall_live_val(_pwall_live);

  high_score = _high_score;
}

int Settings::change_shot_cooldown(uint32_t inp) {
  if (inp > SETTINGS_MAX_SHOT_COOLDOWN) {
    return -EXIT_FAILURE;
  }

  shot_cooldown = inp;
  return EXIT_SUCCESS;
}

int Settings::change_enemy_speed(int inp) {
  switch (inp) {

  case SETTINGS_ENEMY_SPEED_FAST:
    enemy_speed = SETTINGS_ENEMY_SPEED_FAST;
    break;

  case SETTINGS_ENEMY_SPEED_NORMAL:
    enemy_speed = SETTINGS_ENEMY_SPEED_NORMAL;
    break;

  case SETTINGS_ENEMY_SPEED_SLOW:
    enemy_speed = SETTINGS_ENEMY_SPEED_SLOW;
    break;

  default:
    return -EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

uint32_t Settings::get_enemy_speed_fg() {
  switch (enemy_speed) {

  case SETTINGS_ENEMY_SPEED_FAST:
    return SETTINGS_ENEMY_SPEED_FG_FAST;

  case SETTINGS_ENEMY_SPEED_NORMAL:
    return SETTINGS_ENEMY_SPEED_FG_NORMAL;

  case SETTINGS_ENEMY_SPEED_SLOW:
    return SETTINGS_ENEMY_SPEED_FG_SLOW;

  default:
    return -EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int Settings::change_bomb_chance(int inp) {
  switch (inp) {

  case SETTINGS_WEAPON_CHANGE_HIGH:
    bomb_chance = SETTINGS_WEAPON_CHANGE_HIGH;
    break;

  case SETTINGS_WEAPON_CHANGE_NORMAL:
    bomb_chance = SETTINGS_WEAPON_CHANGE_NORMAL;
    break;

  case SETTINGS_WEAPON_CHANGE_LOW:
    bomb_chance = SETTINGS_WEAPON_CHANGE_LOW;
    break;

  default:
    return -EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int Settings::change_nuke_chance(int inp) {
  switch (inp) {

  case SETTINGS_WEAPON_CHANGE_HIGH:
    nuke_chance = SETTINGS_WEAPON_CHANGE_HIGH;
    break;

  case SETTINGS_WEAPON_CHANGE_NORMAL:
    nuke_chance = SETTINGS_WEAPON_CHANGE_NORMAL;
    break;

  case SETTINGS_WEAPON_CHANGE_LOW:
    nuke_chance = SETTINGS_WEAPON_CHANGE_LOW;
    break;

  default:
    return -EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int Settings::change_pwall_cnt(uint8_t inp) {
  if (inp > SETTINGS_MAX_PWALL_CNT) {
    return -EXIT_FAILURE;
  }

  pwall_cnt = inp;
  return EXIT_SUCCESS;
}

int Settings::change_pwall_live(uint8_t inp) {
  if (inp > SETTINGS_MAX_PWALL_LIVE) {
    return -EXIT_FAILURE;
  }

  pwall_live = inp;
  return EXIT_SUCCESS;
}

uint8_t Settings::get_shot_cooldown() { return shot_cooldown; }

uint8_t Settings::get_enemy_speed() { return enemy_speed; }
std::string Settings::get_enemy_speed_string() {

  switch (enemy_speed) {
  case 0:
    return "slow";

  case 1:
    return "normal";

  case 2:
    return "fast";

  default:
    return "";
  }
}

uint8_t Settings::get_bomb_chance() { return bomb_chance; };
std::string Settings::get_bomb_chance_string() {

  switch (bomb_chance) {
  case 0:
    return "low";

  case 1:
    return "normal";

  case 2:
    return "high";

  default:
    return "";
  }
}

uint8_t Settings::get_nuke_chance() { return nuke_chance; }
char *Settings::get_nuke_chance_string() {

  switch (nuke_chance) {
  case 0:
    return (char *)"low";

  case 1:
    return (char *)"normal";

  case 2:
    return (char *)"high";

  default:
    return NULL;
  }
}

uint8_t Settings::get_pwall_cnt() { return pwall_cnt; };

uint8_t Settings::get_pwall_live() { return pwall_live; };

uint32_t Settings::get_high_score() { return high_score; };
