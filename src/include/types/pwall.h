#ifndef PWALL_H
#define PWALL_H

class Pwall {
public:
  Pwall();
  Pwall(int _x, int _y, int live);

  int draw();
  int clean();

  int check_hit(int _x, int _y);
  int d_live();

  int is_alive();

private:
  int x;
  int y;

  int live;
};

#endif
