#include <cstdlib>
#include <stdio.h>

#include "core/hndlrs/destroyer_cntrl.h"
#include "core/utils.h"

#define DESTROYER_AMOUNT 5

#define EXIT_ERROR_DRAW 2
#define EXIT_ERROR_FREE 3

int main() {

  struct destroyer_cntrl_ctx *destroyer_ctx =
      init_destroyer_cntrl(DESTROYER_AMOUNT);
  if (destroyer_ctx == NULL) {
    return -EXIT_FAILURE;
  }

  __init_scr();

  if (destroyer_cntrl_draw(destroyer_ctx) != EXIT_SUCCESS) {
    return -EXIT_ERROR_DRAW;
  }

  if (free_destroyer_cntrl(destroyer_ctx) != EXIT_SUCCESS)
    return -EXIT_ERROR_FREE;

  __free_scr();

  return EXIT_SUCCESS;
}
