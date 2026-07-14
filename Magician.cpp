#include "Magician.h"
#include <iostream>
using namespace std;

Magician::Magician(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    setJob("마법사");
    setMp(getMp() + 30);
    cout << "* 마법사로 전직하였습니다. (MP +30)" << endl;
}

void Magician::attack() {
    cout << "* 파이어볼을 발사한다!" << endl;
}
