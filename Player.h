#pragma once
#include <string>
using namespace std;

class Monster;

class Player {
protected:
    string name;
    string job;
    int level;
    int exp;
    int maxExp;
    int hp;
    int maxHp;
    int mp;
    int maxMp;
    int power;
    int defence;

public:
    Player(string name, int hp, int mp, int power, int defence);
    virtual ~Player() {}

    string getName() const;
    void setName(string name);

    string getJob() const;
    void setJob(string job);

    int getLevel() const;
    void setLevel(int level);

    int getExp() const;
    void setExp(int exp);

    int getMaxExp() const;
    void setMaxExp(int maxExp);

    int getHP() const;
    void setHP(int hp);

    int getMaxHP() const;
    void setMaxHP(int maxHp);

    int getMp() const;
    void setMp(int mp);

    int getMaxMP() const;
    void setMaxMP(int maxMp);

    int getPower() const;
    void setPower(int power);

    int getDefence() const;
    void setDefence(int defence);

    void printPlayerStatus();

    virtual void attack(Monster* monster) = 0;
};
