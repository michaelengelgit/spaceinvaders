#include <cstdlib>
#include <stdio.h>

#include "core/hndlrs/bomber_cntrl.h"
#include "core/utils.h"

#define BOMBER_AMOUNT 5

#define EXIT_ERROR_DRAW 2
#define EXIT_ERROR_FREE 3

int main() {

  struct bomber_cntrl_ctx *bomber_ctx = init_bomber_cntrl(BOMBER_AMOUNT);
  if (bomber_ctx == NULL) {
    return -EXIT_FAILURE;
  }

  __init_scr();

  if (bomber_cntrl_draw(bomber_ctx) != EXIT_SUCCESS) {
    return -EXIT_ERROR_DRAW;
  }

  if (free_bomber_cntrl(bomber_ctx) != EXIT_SUCCESS)
    return -EXIT_ERROR_FREE;

  __free_scr();

  return EXIT_SUCCESS;
}
