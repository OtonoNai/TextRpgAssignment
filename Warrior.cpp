#include "Warrior.h"
#include <iostream>
using namespace std;

Warrior::Warrior(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    setJob("전사");
    setHp(getHp() + 30);
    cout << "* 전사로 전직하였습니다. (HP +30)" << endl;
}

void Warrior::attack() {
    cout << "* 강력한 일격을 날린다!" << endl;
}
