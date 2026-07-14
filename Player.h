#pragma once
#include <string>
using namespace std;

class Player {
protected:
    string name;
    string job;
    int level;
    int hp;
    int mp;
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

    int getHp() const;
    void setHp(int hp);

    int getMp() const;
    void setMp(int mp);

    int getPower() const;
    void setPower(int power);

    int getDefence() const;
    void setDefence(int defence);

    void printPlayerStatus();

    virtual void attack() = 0;
};
