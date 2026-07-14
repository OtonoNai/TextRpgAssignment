#include "Archer.h"
#include <iostream>
using namespace std;

Archer::Archer(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    setJob("궁수");
    setDefence(getDefence() + 30);
    cout << "* 궁수로 전직하였습니다. (방어력 +30)" << endl;
}

void Archer::attack() {
    cout << "* 화살을 쏜다!" << endl;
}
