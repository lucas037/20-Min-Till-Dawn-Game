#ifndef UPGRADEDESCRIPTION_H
#define UPGRADEDESCRIPTION_H

#include "Object.h"
#include "Sprite.h"
#include "Upgrade.h"
#include <string>

class UpgradeDescription : public Object {
private:
    Sprite* sprite;
    std::string title;
    std::string description;
    UpgradeData upgrade;
    int upgradeId;

public:
    UpgradeDescription(const std::string& title, const std::string& description);
    ~UpgradeDescription();

    void Update() override;
    void Draw() override;
};

#endif