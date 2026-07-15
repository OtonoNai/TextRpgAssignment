#pragma once
#include "Player.h"

class Monster;

class Magician : public Player {
public:
    Magician(string name, int hp, int mp, int power, int defence);
    void attack(Monster* monster) override;
};
