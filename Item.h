#pragma once
#include <string>
#include <iostream>
using namespace std;

struct Item {
    string name;
    int price;

    void PrintInfo() const {
        cout << name << " (" << price << "G)";
    }
};
