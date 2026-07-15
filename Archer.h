#pragma once
#include "Player.h"

class Monster;

class Archer : public Player {
public:
    Archer(string name, int hp, int mp, int power, int defence);
    void attack(Monster* monster) override;
};
