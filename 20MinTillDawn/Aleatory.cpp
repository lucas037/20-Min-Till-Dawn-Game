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