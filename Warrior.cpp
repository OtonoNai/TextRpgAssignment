#include "Warrior.h"
#include "Monster.h"
#include <iostream>
using namespace std;

Warrior::Warrior(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    setJob("전사");
    setHP(getHP() + 30);
    setMaxHP(getMaxHP() + 30);
    cout << "* 전사로 전직하였습니다. (HP +30)" << endl;
}

void Warrior::attack(Monster* monster) {
    int damage = getPower() - monster->getDefence();
    if (damage <= 0) {
        damage = 1;
    }

    monster->setHP(monster->getHP() - damage);
    cout << "[전사] 장검을 휘두른다! -> " << monster->getName() << "에게 " << damage << " 데미지!" << endl;
}
