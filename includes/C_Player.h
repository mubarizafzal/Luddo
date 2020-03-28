#include <random>

#ifndef C_PLAYER_H
#define C_PLAYER_H

// random number generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> uid(1, 6);

class C_Player : public Player {

public:

  void set_die () {

    this->die_rolls[0] = uid(gen);
    this->die_rolls[1] = uid(gen);

  }

};

#endif // C_PLAYER_H
