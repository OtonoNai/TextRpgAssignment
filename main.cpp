#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "Player.h"
#include "Warrior.h"
#include "Magician.h"
#include "Thief.h"
#include "Archer.h"
#include "Monster.h"
#include "Item.h"
#include "AlchemyWorkshop.h"
using namespace std;

void printStatus(string name, int stat[]) {
    cout << "====================================" << endl;
    cout << "  " << name << " 의 현재 능력치" << endl;
    cout << "====================================" << endl;
    cout << "HP: " << stat[0] << "    MP: " << stat[1] << endl;
    cout << "공격력: " << stat[2] << "    방어력: " << stat[3] << endl;
    cout << "====================================" << endl;
}

void setPotion(int count, int* p_HPPotion, int* p_MPPotion) {
    *p_HPPotion = count;
    *p_MPPotion = count;
}

void battle(Player* player, Monster& monster, vector<Item>& inventory) {
    cout << endl;
    cout << "[ 전투 시작! ] " << player->getName() << "(" << player->getJob() << ") vs " << monster.getName() << endl;

    while (player->getHP() > 0 && monster.getHP() > 0) {
        cout << endl;
        cout << "--- 플레이어 턴 ---" << endl;
        player->attack();

        int damage = player->getPower() - monster.getDefence();
        if (damage <= 0) {
            damage = 1;
        }

        int beforeHp = monster.getHP();
        monster.setHP(monster.getHP() - damage);

        cout << monster.getName() << "에게 " << damage << " 데미지!" << endl;
        cout << monster.getName() << " HP: " << beforeHp << " -> " << monster.getHP();
        if (monster.getHP() <= 0) {
            cout << " (사망)" << endl;
            break;
        }
        cout << endl;

        cout << endl;
        cout << "--- 몬스터 턴 ---" << endl;
        monster.attack(player);
        if (player->getHP() <= 0) {
            break;
        }
    }

    cout << endl;
    if (monster.getHP() <= 0) {
        cout << "★ 전투 승리!" << endl;
        cout << "  -> " << monster.getDropItemName() << " 획득!" << endl;

        Item droppedItem;
        droppedItem.name = monster.getDropItemName();
        droppedItem.price = monster.getDropItemPrice();
        inventory.push_back(droppedItem);

        cout << "  -> 인벤토리에 저장되었습니다." << endl;
    } else {
        cout << "★ 전투 패배..." << endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand(static_cast<unsigned int>(time(nullptr)));

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

    int hpPotion = 0;
    int mpPotion = 0;
    setPotion(5, &hpPotion, &mpPotion);

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

    vector<Item> inventory;
    const int INVENTORY_MAX = 10;
    AlchemyWorkshop workshop;

    bool isPlaying = true;
    while (isPlaying) {
        cout << endl;
        cout << "=== 메인 메뉴 ===" << endl;
        cout << "1. 던전 입장" << endl;
        cout << "2. 인벤토리 확인" << endl;
        cout << "3. 포션 제작소" << endl;
        cout << "0. 게임 종료" << endl;
        cout << endl;
        cout << "선택: ";
        int menuChoice;
        cin >> menuChoice;

        switch (menuChoice) {
        case 1: {
            int monsterType = rand() % 2;
            if (monsterType == 0) {
                Monster monster("슬라임", 30, 20, 10, "슬라임의 끈적한 젤리", 30);
                battle(player, monster, inventory);
            } else {
                Monster monster("고블린", 40, 15, 5, "고블린의 이빨", 20);
                battle(player, monster, inventory);
            }
            if (player->getHP() <= 0) {
                isPlaying = false;
            }
            break;
        }
        case 2: {
            cout << "[ 인벤토리 (" << inventory.size() << "/" << INVENTORY_MAX << ") ]" << endl;
            int idx = 1;
            for (const Item& item : inventory) {
                cout << idx << ". ";
                item.PrintInfo();
                cout << endl;
                idx++;
            }
            break;
        }
        case 3: {
            bool inShop = true;
            while (inShop) {
                cout << endl;
                cout << "=== 포션 제작소 ===" << endl;
                cout << "1. 전체 레시피 보기" << endl;
                cout << "2. 포션 이름으로 검색" << endl;
                cout << "3. 재료로 검색" << endl;
                cout << "0. 돌아가기" << endl;
                cout << endl;
                cout << "선택: ";
                int shopChoice;
                cin >> shopChoice;

                switch (shopChoice) {
                case 1:
                    workshop.ShowAllRecipes();
                    break;
                case 2: {
                    cout << "검색할 포션 이름: ";
                    string searchName;
                    cin >> searchName;
                    workshop.SearchByName(searchName);
                    break;
                }
                case 3: {
                    cout << "검색할 재료: ";
                    string searchIngredient;
                    cin >> searchIngredient;
                    workshop.SearchByIngredient(searchIngredient);
                    break;
                }
                case 0:
                    inShop = false;
                    break;
                default:
                    cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
                    break;
                }
            }
            break;
        }
        case 0:
            cout << "게임을 종료합니다." << endl;
            isPlaying = false;
            break;
        default:
            cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
            break;
        }
    }

    delete player;

    return 0;
}
