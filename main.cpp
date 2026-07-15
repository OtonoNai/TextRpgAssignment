#include <iostream>
#include <string>
#include <algorithm>
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
#include "Inventory.h"
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

void battle(Player* player, Monster& monster, Inventory<Item>& inventory) {
    cout << endl;
    cout << "[ 전투 시작! ] " << player->getName() << "(" << player->getJob() << ") vs " << monster.getName() << endl;

    while (player->getHP() > 0 && monster.getHP() > 0) {
        cout << endl;
        cout << "--- 플레이어 턴 ---" << endl;
        cout << "1. 공격" << endl;
        cout << "2. 아이템 사용" << endl;
        cout << "선택: ";
        int turnChoice;
        cin >> turnChoice;

        if (turnChoice == 2) {
            cout << "[ 인벤토리 ]" << endl;
            for (int i = 0; i < inventory.GetSize(); i++) {
                cout << (i + 1) << ". ";
                inventory[i].PrintInfo();
                cout << endl;
            }
            cout << "사용할 아이템 번호: ";
            int itemChoice;
            cin >> itemChoice;

            if (itemChoice >= 1 && itemChoice <= inventory.GetSize()) {
                Item usedItem = inventory[itemChoice - 1];

                if (usedItem.name == "HP 포션") {
                    int beforeHeal = player->getHP();
                    player->setHP(min(player->getHP() + 50, player->getMaxHP()));
                    cout << "* HP 포션 사용! HP 50 회복 (" << beforeHeal << " -> " << player->getHP() << ")" << endl;
                    inventory.RemoveItemAt(itemChoice - 1);
                } else if (usedItem.name == "MP 포션") {
                    int beforeHeal = player->getMp();
                    player->setMp(min(player->getMp() + 50, player->getMaxMP()));
                    cout << "* MP 포션 사용! MP 50 회복 (" << beforeHeal << " -> " << player->getMp() << ")" << endl;
                    inventory.RemoveItemAt(itemChoice - 1);
                } else {
                    cout << "* 전투 중에는 사용할 수 없는 아이템입니다." << endl;
                }
            } else {
                cout << "잘못된 번호입니다." << endl;
            }
        } else {
            int beforeHp = monster.getHP();
            player->attack(&monster);

            cout << monster.getName() << " HP: " << beforeHp << " -> " << monster.getHP();
            if (monster.getHP() <= 0) {
                cout << " (사망)" << endl;
                break;
            }
            cout << endl;
        }

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
        inventory.AddItem(droppedItem);

        cout << "  -> 인벤토리에 저장되었습니다." << endl;

        int expGain = monster.getExpReward();
        player->setExp(player->getExp() + expGain);
        cout << "  -> 경험치 +" << expGain << " 획득! (현재 경험치: " << player->getExp() << "/" << player->getMaxExp() << ")" << endl;

        while (player->getExp() >= player->getMaxExp()) {
            int oldLevel = player->getLevel();
            int overflowExp = player->getExp() - player->getMaxExp();

            player->setLevel(oldLevel + 1);
            player->setExp(overflowExp);
            player->setMaxExp(player->getMaxExp() + 50);

            player->setHP(player->getHP() + 10);
            player->setMaxHP(player->getMaxHP() + 10);
            player->setMp(player->getMp() + 5);
            player->setMaxMP(player->getMaxMP() + 5);
            player->setPower(player->getPower() + 5);

            cout << "  -> 레벨 업! Lv." << oldLevel << " -> Lv." << player->getLevel() << endl;
            cout << "  -> HP +10, MP +5, 공격력 +5 증가!" << endl;
        }
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

    player->printPlayerStatus();

    const int INVENTORY_MAX = 10;
    Inventory<Item> inventory(INVENTORY_MAX);
    AlchemyWorkshop workshop;

    for (int i = 0; i < 3; i++) {
        inventory.AddItem({ "HP 포션", 50 });
    }
    for (int i = 0; i < 3; i++) {
        inventory.AddItem({ "MP 포션", 50 });
    }

    bool isPlaying = true;
    while (isPlaying) {
        cout << endl;
        cout << "=== 메인 메뉴 ===" << endl;
        cout << "1. 던전 입장" << endl;
        cout << "2. 인벤토리 확인" << endl;
        cout << "3. 포션 제작소" << endl;
        cout << "4. 인벤토리 정렬(가격순)" << endl;
        cout << "0. 게임 종료" << endl;
        cout << endl;
        cout << "선택: ";
        int menuChoice;
        cin >> menuChoice;

        switch (menuChoice) {
        case 1: {
            int monsterType = rand() % 2;
            if (monsterType == 0) {
                Monster monster("슬라임", 30, 20, 10, "슬라임의 끈적한 젤리", 30, 30);
                battle(player, monster, inventory);
            } else {
                Monster monster("고블린", 40, 15, 5, "고블린의 이빨", 20, 40);
                battle(player, monster, inventory);
            }
            if (player->getHP() <= 0) {
                isPlaying = false;
            }
            break;
        }
        case 2: {
            inventory.PrintAllItems();
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
                cout << "4. 포션 지급받기" << endl;
                cout << "5. 공병 반환하기" << endl;
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
                case 4: {
                    cout << "지급받을 포션 이름: ";
                    string potionName;
                    cin >> potionName;
                    cout << potionName << " 재고: " << workshop.GetStock(potionName) << endl;
                    workshop.DispensePotion(potionName);
                    break;
                }
                case 5: {
                    cout << "반환할 포션 이름: ";
                    string potionName;
                    cin >> potionName;
                    workshop.ReturnPotion(potionName);
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
        case 4: {
            inventory.SortItems(compareByPrice);
            cout << "[ 가격순 정렬 후 인벤토리 ]" << endl;
            for (int i = 0; i < inventory.GetSize(); i++) {
                cout << (i + 1) << ". ";
                inventory[i].PrintInfo();
                cout << endl;
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
