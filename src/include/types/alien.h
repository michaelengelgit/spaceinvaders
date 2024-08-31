#ifndef ALIEN_H
#define ALIEN_H

#define ALIEN_LENGTH 5
#define ALIEN_ALIVE 1
#define ALIEN_NALIVE 0

class Alien {
public:
  Alien();
  Alien(int _x, int _y, int _alive);

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
