#include "Thief.h"
#include <iostream>
using namespace std;

Thief::Thief(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    setJob("도적");
    setPower(getPower() + 30);
    cout << "* 도적으로 전직하였습니다. (공격력 +30)" << endl;
}

void Thief::attack() {
    cout << "* 은신 후 급소를 찌른다!" << endl;
}
