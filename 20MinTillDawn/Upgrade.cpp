#include "Upgrade.h"

const UpgradeData Upgrade::upgrades[] = {
    { "Berserker Shot", "Increase your weapon damage by 25%.", SK_DAMAGE, 0 },
    { "Swift Boots", "Move 20% faster.", SK_SPEED, 1 },
    { "Iron Heart", "Gain an extra 50 HP.", SK_HEALTH, 20 },
    { "Rapid Fire", "Shoot 30% faster.", SK_ATTACK_SPEED, 3 },
    { "Explosive Rounds", "Bullets deal area damage.", SK_AREA_DAMAGE, 4 }
};

UpgradeData Upgrade::GetUpgrade(int index) {
    int count = GetUpgradeCount();
    if (index < 0 || index >= count)
        return { "Unknown", "Invalid upgrade index.", SK_DAMAGE, -1 };

    return upgrades[index];
}

int Upgrade::GetUpgradeCount() {
    return sizeof(upgrades) / sizeof(UpgradeData);
}
