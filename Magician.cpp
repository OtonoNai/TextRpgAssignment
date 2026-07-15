#include "Magician.h"
#include "Monster.h"
#include <iostream>
using namespace std;

Magician::Magician(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    setJob("마법사");
    setMp(getMp() + 30);
    cout << "* 마법사로 전직하였습니다. (MP +30)" << endl;
}

void Magician::attack(Monster* monster) {
    int damage = getPower() - monster->getDefence();
    if (damage <= 0) {
        damage = 1;
    }

    monster->setHP(monster->getHP() - damage);
    cout << "[마법사] 파이어볼 발사! -> " << monster->getName() << "에게 " << damage << " 데미지!" << endl;
}
