#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(string name, int hp, int mp, int power, int defence)
    : name(name), job(""), level(1), hp(hp), mp(mp), power(power), defence(defence) {
}

string Player::getName() const { return name; }
void Player::setName(string name) { this->name = name; }

string Player::getJob() const { return job; }
void Player::setJob(string job) { this->job = job; }

int Player::getLevel() const { return level; }
void Player::setLevel(int level) { this->level = level; }

int Player::getHp() const { return hp; }
void Player::setHp(int hp) { this->hp = hp; }

int Player::getMp() const { return mp; }
void Player::setMp(int mp) { this->mp = mp; }

int Player::getPower() const { return power; }
void Player::setPower(int power) { this->power = power; }

int Player::getDefence() const { return defence; }
void Player::setDefence(int defence) { this->defence = defence; }

void Player::printPlayerStatus() {
    cout << "------------------------------------" << endl;
    cout << "닉네임: " << name << " | 직업: " << job << " | Lv." << level << endl;
    cout << "HP: " << hp << " | MP: " << mp << " | 공격력: " << power << " | 방어력: " << defence << endl;
    cout << "------------------------------------" << endl;
}
