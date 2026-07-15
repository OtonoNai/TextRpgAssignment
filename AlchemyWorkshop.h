#pragma once
#include <vector>
#include <string>
#include <map>
#include "PotionRecipe.h"
using namespace std;

class AlchemyWorkshop {
private:
    vector<PotionRecipe> recipes;
    map<string, int> potionStock_;

    static const int MAX_STOCK = 3;

public:
    AlchemyWorkshop();

    void ShowAllRecipes() const;
    void SearchByName(string name) const;
    void SearchByIngredient(string ingredient) const;

    void DispensePotion(const string& name);
    void ReturnPotion(const string& name);
    int GetStock(const string& name) const;
};
