#include <iostream>
#include <string>
#include <Windows.h>
#include "Player.h"
#include "Warrior.h"
#include "Magician.h"
#include "Thief.h"
#include "Archer.h"
using namespace std;

void printStatus(string name, int stat[]) {
    cout << "====================================" << endl;
    cout << "  " << name << " 의 현재 능력치" << endl;
    cout << "====================================" << endl;
    cout << "HP: " << stat[0] << "    MP: " << stat[1] << endl;
    cout << "공격력: " << stat[2] << "    방어력: " << stat[3] << endl;
    cout << "====================================" << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const int SIZE = 4;
    int stat[SIZE] = {0};
    string name;

    cout << "===========================================" << endl;
    cout << "   [ 던전 탈출 텍스트 RPG ]" << endl;
    cout << "===========================================" << endl;
    cout << "용사의 이름을 입력해주세요: ";
    cin >> name;

    cout << endl;
    while (true) {
        cout << "HP와 MP를 입력해주세요: ";
        cin >> stat[0] >> stat[1];
        if (stat[0] > 50 && stat[1] > 50) {
            break;
        }
        cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요." << endl;
    }

    while (true) {
        cout << "공격력과 방어력을 입력해주세요: ";
        cin >> stat[2] >> stat[3];
        if (stat[2] > 0 && stat[3] > 0) {
            break;
        }
        cout << "공격력이나 방어력이 너무 작습니다. 다시 입력해주세요." << endl;
    }

    cout << endl;
    printStatus(name, stat);

    int hpPotion = 5;
    int mpPotion = 5;

    cout << "* HP 포션 " << hpPotion << "개, MP 포션 " << mpPotion << "개가 기본 지급되었습니다." << endl;
    cout << "============================================" << endl;
    cout << "< 캐릭터 강화 >" << endl;
    cout << "1. HP UP    2. MP UP    3. 공격력 2배" << endl;
    cout << "4. 방어력 2배  5. 현재 능력치  0. 게임 시작" << endl;
    cout << "============================================" << endl;

    bool isGameStart = false;
    while (!isGameStart) {
        cout << "번호를 선택해주세요: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            if (hpPotion > 0) {
                stat[0] += 20;
                hpPotion--;
                cout << "* HP가 20 증가했습니다. (HP 포션 차감: 남은 포션 " << hpPotion << "개)" << endl;
            } else {
                cout << "* HP 포션이 부족합니다." << endl;
            }
            break;
        case 2:
            if (mpPotion > 0) {
                stat[1] += 20;
                mpPotion--;
                cout << "* MP가 20 증가했습니다. (MP 포션 차감: 남은 포션 " << mpPotion << "개)" << endl;
            } else {
                cout << "* MP 포션이 부족합니다." << endl;
            }
            break;
        case 3:
            stat[2] *= 2;
            cout << "* 공격력이 2배가 되었습니다. (현재 공격력: " << stat[2] << ")" << endl;
            break;
        case 4:
            stat[3] *= 2;
            cout << "* 방어력이 2배가 되었습니다. (현재 방어력: " << stat[3] << ")" << endl;
            break;
        case 5:
            printStatus(name, stat);
            break;
        case 0:
            cout << "게임을 시작합니다!" << endl;
            isGameStart = true;
            break;
        default:
            cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
            break;
        }
    }

    cout << endl;
    cout << "< 전직 시스템 >" << endl;
    cout << name << "님, 직업을 선택해주세요!" << endl;
    cout << "1. 전사   2. 마법사   3. 도적   4. 궁수" << endl;
    cout << "선택: ";
    int jobChoice;
    cin >> jobChoice;

    Player* player = nullptr;
    switch (jobChoice) {
    case 1:
        player = new Warrior(name, stat[0], stat[1], stat[2], stat[3]);
        break;
    case 2:
        player = new Magician(name, stat[0], stat[1], stat[2], stat[3]);
        break;
    case 3:
        player = new Thief(name, stat[0], stat[1], stat[2], stat[3]);
        break;
    case 4:
        player = new Archer(name, stat[0], stat[1], stat[2], stat[3]);
        break;
    default:
        player = new Warrior(name, stat[0], stat[1], stat[2], stat[3]);
        break;
    }

    player->attack();
    player->printPlayerStatus();

    delete player;

    return 0;
}
