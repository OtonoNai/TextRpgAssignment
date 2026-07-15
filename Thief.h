#pragma once
#include "Player.h"

class Monster;

class Thief : public Player {
public:
    Thief(string name, int hp, int mp, int power, int defence);
    void attack(Monster* monster) override;
};
