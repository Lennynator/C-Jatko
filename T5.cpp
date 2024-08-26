#include <iostream>
#include <vector>
#include <algorithm> // std::for_each, std::sort

// a. Erillinen funktio
void reduceHP(int& hp) {
    if (hp > 100)
        hp -= 100;
    else
        hp = 0;
}

// b. Funktio-objekti
struct HPReducer {
    void operator()(int& hp) const {
        if (hp > 100)
            hp -= 100;
        else
            hp = 0;
    }
};

int main() {
    std::vector<int> enemyHPs = { 150, 120, 300, 90, 200 };

    // a. Erillinen funktio
    std::for_each(enemyHPs.begin(), enemyHPs.end(), reduceHP);

    // Tulosta tulos
    std::cout << "After reduction with function: ";
    for (const auto& hp : enemyHPs) std::cout << hp << " ";
    std::cout << std::endl;

    // b. funktio-objekti
    std::for_each(enemyHPs.begin(), enemyHPs.end(), HPReducer());

    // Tulosta tulos
    std::cout << "After reduction with functor: ";
    for (const auto& hp : enemyHPs) std::cout << hp << " ";
    std::cout << std::endl;

    // c lambda-funktio
    std::for_each(enemyHPs.begin(), enemyHPs.end(), [](int& hp) {
        if (hp > 100)
            hp -= 100;
        else
            hp = 0;
        });

    // Tulosta tulos
    std::cout << "After reduction with lambda: ";
    for (const auto& hp : enemyHPs) std::cout << hp << " ";
    std::cout << std::endl;

    // d. Nimetty lambda-funktio
    auto namedLambdaReducer = [](int& hp) {
        if (hp > 100)
            hp -= 100;
        else
            hp = 0;
        };
    std::for_each(enemyHPs.begin(), enemyHPs.end(), namedLambdaReducer);

    // Tulosta tulos
    std::cout << "After reduction with named lambda: ";
    for (const auto& hp : enemyHPs) std::cout << hp << " ";
    std::cout << std::endl;

    // Järjestä vektori
    std::sort(enemyHPs.begin(), enemyHPs.end(), [](int a, int b) {
        return a > b; // laskeva järjestys
        });

    // Tulosta 
    std::cout << "Sorted in descending order: ";
    for (const auto& hp : enemyHPs) std::cout << hp << " ";
    std::cout << std::endl;

    return 0;
}
