#ifndef UPGRADE_H
#define UPGRADE_H

#include <string>
using namespace std;

enum UpgradeType {
    SK_DAMAGE,
    SK_SPEED,
    SK_HEALTH,
    SK_ATTACK_SPEED,
    SK_AREA_DAMAGE
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
