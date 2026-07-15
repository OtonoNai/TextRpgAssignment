#include "Thief.h"
#include "Monster.h"
#include <iostream>
using namespace std;

Thief::Thief(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    setJob("도적");
    setPower(getPower() + 30);
    cout << "* 도적으로 전직하였습니다. (공격력 +30)" << endl;
}

void Thief::attack(Monster* monster) {
    int damage = getPower() / 5 - monster->getDefence();
    if (damage <= 0) {
        damage = 1;
    }

    for (int i = 0; i < 5; i++) {
        monster->setHP(monster->getHP() - damage);
    }

    cout << "[도적] 단검을 찌른다! -> " << monster->getName() << "에게 " << damage << " 데미지! (x5)" << endl;
}
