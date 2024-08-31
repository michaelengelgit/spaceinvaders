#include <cstdlib>
#include <stdio.h>

#include "core/hndlrs/alien_cntrl.h"
#include "core/utils.h"

#define ALIEN_AMOUNT 5

#define EXIT_ERROR_DRAW 2
#define EXIT_ERROR_FREE 3

int main() {

  struct alien_cntrl_ctx *alien_ctx = init_alien_cntrl(ALIEN_AMOUNT);
  if (alien_ctx == NULL) {
    return -EXIT_FAILURE;
  }

  __init_scr();

  if (alien_cntrl_draw(alien_ctx) != EXIT_SUCCESS) {
    return -EXIT_ERROR_DRAW;
  }

  if (free_alien_cntrl(alien_ctx) != EXIT_SUCCESS)
    return -EXIT_ERROR_FREE;

  __free_scr();

  return EXIT_SUCCESS;
}
