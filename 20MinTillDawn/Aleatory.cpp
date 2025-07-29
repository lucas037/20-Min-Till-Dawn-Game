#include "Aleatory.h" // Inclui a declara��o da classe
#include <iostream>  // Para usar std::cout
#include <cstdlib>   // Para usar std::rand e std::srand
#include <ctime>     // Para usar std::time

int Aleatory::randrange(int a, int b) {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    return std::rand() % (b - a) + a;
}

static std::vector<int> GenerateNumbersList(int count, int min, int max, bool allowRepeat) {
    std::vector<int> result;

    if (!allowRepeat && count > (max - min)) {
        return result;
    }

    while (result.size() < count) {
        int num = Aleatory::randrange(min, max);
        if (allowRepeat || std::find(result.begin(), result.end(), num) == result.end()) {
            result.push_back(num);
        }
    }

    return result;
}
