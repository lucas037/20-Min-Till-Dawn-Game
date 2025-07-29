#ifndef ALEATORY_H
#define ALEATORY_H

#include <vector>
#include "Vector.h"

class Aleatory {
public:
    static int randrange(int a, int b);
    static std::vector<int> GenerateNumbersList(int count, int min, int max, bool allowRepeat);
};

#endif
