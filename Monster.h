#pragma once
#include <string>
#include "Player.h"
using namespace std;

class Monster {
private:
    string name;
    int hp;
    int power;
    int defence;
    string dropItemName;
    int dropItemPrice;
    int expReward;

public:
    Monster(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward);

    string getName() const;

    int getHP() const;
    void setHP(int hp);

    int getPower() const;
    int getDefence() const;

    string getDropItemName() const;
    int getDropItemPrice() const;
    int getExpReward() const;

    void attack(Player* player);
};
