#ifndef TOML_H
#define TOML_H

#include "lib/toml/toml.hpp"
#include "types/settings.h"

#define DOT_CONFIG_DIR ".config"
#define GAME_CONFIG_DIR "spaceinvaders"

#define GAME_CONFIG_FILE "config.toml"

Settings settings_init();
Settings create_setting(toml::table tbl);

int toml_write_settings(Settings *settings);

#endif
