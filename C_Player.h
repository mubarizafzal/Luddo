#ifndef C_PLAYER_H
#define C_PLAYER_H

class C_Player : public Player {

public:

  void set_die () {

    this->die_rolls[0] = (rand() % 6) + 1;
    this->die_rolls[1] = (rand() % 6) + 1;

  }

};

#endif // C_PLAYER_H
