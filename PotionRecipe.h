#pragma once
#include <string>
using namespace std;

struct Ingredient {
    string name;
    int count;
};

struct PotionRecipe {
    string name;
    Ingredient ingredients[2];
};
