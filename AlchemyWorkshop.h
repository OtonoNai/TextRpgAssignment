#pragma once
#include <vector>
#include <string>
#include "PotionRecipe.h"
using namespace std;

class AlchemyWorkshop {
private:
    vector<PotionRecipe> recipes;

public:
    AlchemyWorkshop();

    void ShowAllRecipes() const;
    void SearchByName(string name) const;
    void SearchByIngredient(string ingredient) const;
};
