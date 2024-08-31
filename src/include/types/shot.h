#ifndef SHOT_H
#define SHOT_H

#include <inttypes.h>

class Shot {
public:
  Shot();
  Shot(int _x, int _y, char sym);

  int draw();
  int clean();

  int mv_u();
  int mv_d();

  int set_xy(int _x, int _y);
  int set_inactive();

  int set_active();
  int get_active();

  int get_x();
  int get_y();

private:
  int x;
  int y;

  uint8_t active;
  char ch;
};

#endif
