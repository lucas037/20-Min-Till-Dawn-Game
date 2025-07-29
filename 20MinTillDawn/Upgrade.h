#ifndef UPGRADE_H
#define UPGRADE_H

#include <string>
#include "Vector.h"
using namespace std;

enum UpgradeType {
    SK_NONE,
    SK_HEALTH,
    SK_GIANT,
    SK_REGENERATION,
    SK_EVASIVE,
    SK_TINY,
    SK_REFLEX,
    SK_FASTUPGRADE,
    SK_BULLETDAMAGE,
};

struct UpgradeData {
    string name;
    string description;
    UpgradeType type;
    int iconId;
};

class Upgrade {
public:
    static UpgradeData GetUpgrade(int index);
    static int GetUpgradeCount();

private:
    static const UpgradeData upgrades[];
};

#endif
