#include "Archer.h"
#include "Monster.h"
#include <iostream>
using namespace std;

Archer::Archer(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    setJob("궁수");
    setDefence(getDefence() + 30);
    cout << "* 궁수로 전직하였습니다. (방어력 +30)" << endl;
}

void Archer::attack(Monster* monster) {
    int damage = getPower() / 3 - monster->getDefence();
    if (damage <= 0) {
        damage = 1;
    }

    for (int i = 0; i < 3; i++) {
        monster->setHP(monster->getHP() - damage);
    }

    cout << "[궁수] 화살을 쏜다! -> " << monster->getName() << "에게 " << damage << " 데미지! (x3)" << endl;
}
