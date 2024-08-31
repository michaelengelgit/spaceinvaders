#ifndef UTILS_H
#define UTILS_H

#include <inttypes.h>

#define KEY_SPACE 32
#define KEY_q 113
#define KEY_m 109
#define KEY_h 104
#define KEY_s 115
#define KEY_a 97
#define KEY_d 100
#define KEY_p 112
#define KEY_b 98
#define KEY_n 110
#define KEY_f 102
#define KEY_l 108

#define _KEY_A 65
#define _KEY_B 66
#define _KEY_C 67
#define _KEY_D 68
#define _KEY_E 69
#define _KEY_F 70

#define EXIT_START_GAME 1
#define EXIT_QUIT_GAME 2

#define EXIT_HELP_GAME 3
#define EXIT_MENU_GAME 4

#define EXIT_START_MENU 5
#define EXIT_CONTINUE_GAME 6
#define EXIT_WON_GAME 7

#define UTILS_ONE_OFFSET 1
#define UTILS_NUM_EV 2

#define UTILS_EXIT_ERR 9

int __init_scr();
int __free_scr();

int player_check_exit_border_x(int x, int l);
int check_exit_border_x(int x, int l);

int calc_cnt(int x, int ent_len, int min_gap_len);
int gen_r_nm(uint8_t min, uint8_t max);

#endif
