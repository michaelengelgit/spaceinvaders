#ifndef DESTROYER_H
#define DESTROYER_H

#define DESTROYER_LENGTH 5
#define DESTROYER_ALIVE 1
#define DESTROYER_NALIVE 0

class Destroyer {
public:
  Destroyer();
  Destroyer(int _x, int _y, int _alive);

  int draw();
  int clean(int off);

  int mv_r();
  int mv_l();

  int mv_d();
  int check_hit(int _x, int _y);

  int set_unalive();
  int get_x();

  int get_y();
  int get_alive();

private:
  int x;
  int y;

  int alive;
};

#endif
