#include "Upgrade.h"

const UpgradeData Upgrade::upgrades[] = {
    { "Vitalidade", "Mais de de vida maxima", SK_HEALTH, 2 * 12 + 4 },
    { "Gigante", "Mais 2 de vida maxima e 25% de tamanho", SK_GIANT, 2 * 12 + 5 },
    { "Regeneracao", "Recupere 1 de vida a cada 60 segundos", SK_REGENERATION, 2 * 12 + 7 },
    { "Evasiva", "Desvio mais 25%", SK_EVASIVE, 4 * 12 + 4 },
    { "Pequena", "Desvio mais 5% e tamanho menos 25%", SK_TINY, 8 * 12 + 6 },
    { "Magnetismo", "Tempo para obter upgrades reduzido em 10 segundos", SK_FASTUPGRADE, 7 * 12 + 0 },
    { "Power Shot", "Dano da bala aumenta em 40%", SK_BULLETDAMAGE, 1 * 12 + 0 }
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
