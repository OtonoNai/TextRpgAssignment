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

inline bool compareByPrice(const Item& a, const Item& b) {
    return a.price < b.price;
}
