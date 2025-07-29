#include "Aleatory.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept>

int Aleatory::randrange(int a, int b) {
    if (a >= b) {
        throw std::invalid_argument("Invalid range: 'a' must be less than 'b'.");
    }

    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    return std::rand() % (b - a) + a;
}

std::vector<int> Aleatory::GenerateNumbersList(int count, int min, int max, bool allowRepeat) {
    std::vector<int> result;
    result.reserve(count);

    if (!allowRepeat && count > (max - min)) {
        return result;
    }

    while (result.size() < static_cast<size_t>(count)) {
        int num = Aleatory::randrange(min, max);

        if (allowRepeat) {
            result.push_back(num);
        }
        else {
            if (std::find(result.begin(), result.end(), num) == result.end()) {
                result.push_back(num);
            }
        }
    }

    return result;
}