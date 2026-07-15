#include "Monster.h"
#include "Player.h"
#include <iostream>
using namespace std;

Monster::Monster(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward)
    : name(name), hp(hp), power(power), defence(defence),
      dropItemName(dropItemName), dropItemPrice(dropItemPrice), expReward(expReward) {
}

string Monster::getName() const { return name; }

int Monster::getHP() const { return hp; }
void Monster::setHP(int hp) { this->hp = hp; }

int Monster::getPower() const { return power; }
int Monster::getDefence() const { return defence; }

string Monster::getDropItemName() const { return dropItemName; }
int Monster::getDropItemPrice() const { return dropItemPrice; }
int Monster::getExpReward() const { return expReward; }

void Monster::attack(Player* player) {
    int damage = power - player->getDefence();
    if (damage <= 0) {
        damage = 1;
    }

    int beforeHp = player->getHP();
    player->setHP(player->getHP() - damage);

    cout << name << "이(가) " << player->getName() << "에게 " << damage << " 데미지!" << endl;
    cout << player->getName() << " HP: " << beforeHp << " -> " << player->getHP();
    if (player->getHP() <= 0) {
        cout << " (사망)" << endl;
    } else {
        cout << endl;
    }
}
