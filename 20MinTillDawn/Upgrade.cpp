#include "Upgrade.h"

const UpgradeData Upgrade::upgrades[] = {
    { "Vitalidade", "Vida +1", SK_HEALTH, 2 * 12 + 4 },
    { "Gigante", "+2 de Vida Maxima e 25% de Tamanho", SK_GIANT, 2 * 12 + 5 },
    { "Regeneracao", "Recupere 1 de vida a cada 60 segundos", SK_REGENERATION, 2 * 12 + 7 },
    { "Rapid Fire", "Shoot 30% faster.", SK_NONE, 3 },
    { "Explosive Rounds", "Bullets deal area damage.", SK_NONE, 4 }
};

UpgradeData Upgrade::GetUpgrade(int index) {
    int count = GetUpgradeCount();
    if (index < 0 || index >= count)
        return { "Unknown", "Invalid upgrade index.", SK_NONE, -1 };

    return upgrades[index];
}

int Upgrade::GetUpgradeCount() {
    return sizeof(upgrades) / sizeof(UpgradeData);
}
