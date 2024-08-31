#include <filesystem>
#include <pwd.h>
#include <unistd.h>

#include "lib/toml/toml.hpp"

#include "io/toml.h"

int __create_config_folder(const char *home_dir) {
  if (home_dir == NULL)
    return -EXIT_FAILURE;

  std::string _path;

  _path.append(home_dir).append("/").append(DOT_CONFIG_DIR);

  if (!std::filesystem::is_directory(_path) ||
      !std::filesystem::exists(_path)) {

    std::filesystem::create_directory(_path);
  }

  return EXIT_SUCCESS;
}

int __create_game_folder(const char *home_dir) {
  if (home_dir == NULL)
    return -EXIT_FAILURE;

  std::string _path;

  _path.append(home_dir)
      .append("/")
      .append(DOT_CONFIG_DIR)
      .append("/")
      .append(GAME_CONFIG_DIR);

  if (!std::filesystem::is_directory(_path) ||
      !std::filesystem::exists(_path)) {

    std::filesystem::create_directory(_path);
  }

  return EXIT_SUCCESS;
}

int __create_folders(const char *home_dir) {
  if (home_dir == NULL)
    return -EXIT_FAILURE;

  if (__create_config_folder(home_dir) != EXIT_SUCCESS) {
    return -2;
  }

  if (__create_game_folder(home_dir) != EXIT_SUCCESS) {
    return -3;
  }

  return EXIT_SUCCESS;
}

int __create_default_config_file(std::string path) {
  if (path.empty())
    return -EXIT_FAILURE;

  auto tbl = toml::table{
      {
          "Game",
          toml::table{
              {"shot_cooldown", DEF_SHOT_COOLDOWN},
              {"enemy_speed", DEF_ENEMY_SPEED},
              {"bomb_chance", DEF_BOMB_CHANCE},
              {"nuke_chance", DEF_NUKE_CHANCE},
          },
      },
      {
          "Pwall",
          toml::table{
              {"amount", DEF_PWALL_AMOUNT},
              {"live", DEF_PWALL_LIVE},
          },
      },

      {
          "Saves",
          toml::table{
              {"high_score", 0},
          },
      },
  };

  std::ofstream file(path);
  file << tbl;
  file.close();

  return EXIT_SUCCESS;
}

std::string __get_config_path() {
  struct passwd *pw = getpwuid(getuid());
  const char *home_dir = pw->pw_dir;

  std::string path;
  path.append(home_dir)
      .append("/")
      .append(DOT_CONFIG_DIR)
      .append("/")
      .append(GAME_CONFIG_DIR)
      .append("/")
      .append(GAME_CONFIG_FILE);

  return path;
}

int toml_write_settings(Settings *settings) {
  std::string _path = __get_config_path();

  auto tbl = toml::table{

      {
          "Game",
          toml::table{
              {"shot_cooldown", settings->get_shot_cooldown()},
              {"enemy_speed", settings->get_enemy_speed_string()},
              {"bomb_chance", settings->get_bomb_chance_string()},
              {"nuke_chance", settings->get_nuke_chance_string()},
          },
      },
      {
          "Pwall",
          toml::table{
              {"amount", settings->get_pwall_cnt()},
              {"live", settings->get_pwall_live()},
          },
      },

      {
          "Saves",
          toml::table{
              {"high_score", settings->get_high_score()},
          },
      },
  };

  std::ofstream file(_path);
  file << tbl;
  file.close();

  return EXIT_SUCCESS;
}

Settings create_setting(toml::table tbl) {

  std::string bomb_chance = tbl["Game"]["bomb_chance"].value_or("");

  std::string enemy_speed = tbl["Game"]["enemy_speed"].value_or("");

  std::string nuke_chance = tbl["Game"]["nuke_chance"].value_or("");

  int shot_cooldown = tbl["Game"]["shot_cooldown"].value_or(-EXIT_FAILURE);
  int pwall_amount = tbl["Pwall"]["amount"].value_or(-EXIT_FAILURE);

  int pwall_live = tbl["Pwall"]["live"].value_or(-EXIT_FAILURE);
  int high_score = tbl["Saves"]["high_score"].value_or(-EXIT_FAILURE);

  if (shot_cooldown == -EXIT_FAILURE || pwall_amount == -EXIT_FAILURE ||
      pwall_live == -EXIT_FAILURE || high_score == -EXIT_FAILURE ||
      bomb_chance.empty() || enemy_speed.empty() || nuke_chance.empty() ||
      high_score == -EXIT_FAILURE) {

    return Settings(DEF_SHOT_COOLDOWN, DEF_ENEMY_SPEED, DEF_BOMB_CHANCE,
                    DEF_NUKE_CHANCE, DEF_PWALL_AMOUNT, DEF_PWALL_LIVE, 0);
  }

  else {

    return Settings(shot_cooldown, enemy_speed, bomb_chance, nuke_chance,
                    pwall_amount, pwall_live, high_score);
  }
}

Settings settings_init() {
  struct passwd *pw = getpwuid(getuid());
  const char *home_dir = pw->pw_dir;

  std::string _path = __get_config_path();

  toml::table tbl;
  __create_folders(home_dir);

try_parse:
  try {

    tbl = toml::parse_file(_path);
    return create_setting(tbl);

  }

  catch (const toml::parse_error &err) {

    __create_default_config_file(_path);
    goto try_parse;
  }
}
