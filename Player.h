
#ifndef PLAYER_H
#define PLAYER_H

class Player {

public:

  int id = -1;

  int pieces[4] = {-1, -2, -3, -4};

  int die_rolls[2] = {0, 0};

  int x, y;

  int r, g, b;

  int home;
  int safe;

  // n is which corner the player is, 0 is yellow, 1 is blue, 2 is red, 3 is green

  void set_player (int id, int home, int x, int y, int r, int g, int b) {

    this->id = id;

    this->x = x;
    this->y = y;

    this->r = r;
    this->g = g;
    this->b = b;

    this->home = home;
    this->safe = (home + 52 - 5) % 52;

  }

};
#endif // PLAYER_H
