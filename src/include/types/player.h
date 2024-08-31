#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
  Player();
  Player(int _x, int _y);

  int draw();
  int clean();

  int mv_r();
  int mv_l();

  int mv_d();
  int check_hit(int _x, int _y);

  int get_x();
  int get_y();

private:
  int x;
  int y;
};

#endif
