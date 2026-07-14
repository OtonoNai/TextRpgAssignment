#include "AlchemyWorkshop.h"
#include <iostream>
using namespace std;

AlchemyWorkshop::AlchemyWorkshop() {
    recipes.push_back({ "HP포션", { {"허브", 1}, {"맑은물", 1} } });
    recipes.push_back({ "스태미나포션", { {"허브", 1}, {"베리", 1} } });
}

void AlchemyWorkshop::ShowAllRecipes() const {
    cout << "[ 전체 레시피 목록 ]" << endl;
    int idx = 1;
    for (const PotionRecipe& recipe : recipes) {
        cout << idx << ". " << recipe.name << " ("
             << recipe.ingredients[0].name << " x" << recipe.ingredients[0].count << ", "
             << recipe.ingredients[1].name << " x" << recipe.ingredients[1].count << ")" << endl;
        idx++;
    }
}

void AlchemyWorkshop::SearchByName(string name) const {
    for (const PotionRecipe& recipe : recipes) {
        if (recipe.name == name) {
            cout << "-> " << recipe.name << ": "
                 << recipe.ingredients[0].name << " x" << recipe.ingredients[0].count << ", "
                 << recipe.ingredients[1].name << " x" << recipe.ingredients[1].count << endl;
            return;
        }
    }
    cout << "찾을 수 없습니다" << endl;
}

void AlchemyWorkshop::SearchByIngredient(string ingredient) const {
    int foundCount = 0;
    for (const PotionRecipe& recipe : recipes) {
        if (recipe.ingredients[0].name == ingredient || recipe.ingredients[1].name == ingredient) {
            cout << "-> " << recipe.name << " ("
                 << recipe.ingredients[0].name << " x" << recipe.ingredients[0].count << ", "
                 << recipe.ingredients[1].name << " x" << recipe.ingredients[1].count << ")" << endl;
            foundCount++;
        }
    }
    cout << "총 " << foundCount << "개의 레시피를 찾았습니다." << endl;
}
