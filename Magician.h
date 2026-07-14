#pragma once
#include "Player.h"

class Magician : public Player {
public:
    Magician(string name, int hp, int mp, int power, int defence);
    void attack() override;
};
