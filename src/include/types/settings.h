#ifndef SETTINGS_H
#define SETTINGS_H

#include <inttypes.h>
#include <string>

#define SETTINGS_MAX_SHOT_COOLDOWN 100

#define SETTINGS_ENEMY_SPEED_SLOW 0
#define SETTINGS_ENEMY_SPEED_NORMAL 1
#define SETTINGS_ENEMY_SPEED_FAST 2

#define SETTINGS_WEAPON_CHANGE_LOW 0
#define SETTINGS_WEAPON_CHANGE_NORMAL 1
#define SETTINGS_WEAPON_CHANGE_HIGH 2

#define SETTINGS_MAX_PWALL_CNT 6
#define SETTINGS_MAX_PWALL_LIVE 50

#define DEF_SHOT_COOLDOWN 2
#define DEF_ENEMY_SPEED "normal"

#define DEF_BOMB_CHANCE "normal"
#define DEF_NUKE_CHANCE "normal"

#define DEF_PWALL_AMOUNT 3
#define DEF_PWALL_LIVE 10

#define SETTINGS_ENEMY_SPEED_FG_SLOW 30000
#define SETTINGS_ENEMY_SPEED_FG_NORMAL 25000
#define SETTINGS_ENEMY_SPEED_FG_FAST 20000

class Settings {
public:
  Settings();
  Settings(uint8_t _shot_cooldown, std::string _enemy_speed,
           std::string _bomb_chance, std::string _nuke_chane,
           uint8_t _pwall_cnt, uint8_t _pwall_live, uint32_t _high_socre);

  int change_shot_cooldown(uint32_t inp);
  int change_enemy_speed(int inp);

  int change_bomb_chance(int inp);
  int change_nuke_chance(int inp);

  int change_pwall_cnt(uint8_t inp);
  int change_pwall_live(uint8_t inp);

  uint8_t get_shot_cooldown();
  int check_new_high_score(int new_score);

  uint8_t get_enemy_speed();
  std::string get_enemy_speed_string();

  uint32_t get_enemy_speed_fg();

  uint8_t get_bomb_chance();
  std::string get_bomb_chance_string();

  uint8_t get_nuke_chance();
  char *get_nuke_chance_string();

  uint8_t get_pwall_cnt();
  uint8_t get_pwall_live();

  uint32_t get_high_score();

private:
  uint32_t shot_cooldown;
  uint8_t enemy_speed;

  uint8_t bomb_chance;
  uint8_t nuke_chance;

  uint8_t pwall_cnt;
  uint8_t pwall_live;

  uint32_t high_score;
};

#endif
