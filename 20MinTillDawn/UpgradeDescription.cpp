#include "UpgradeDescription.h"
#include "MinutesTillDawn.h"
#include "Window.h"

UpgradeDescription::UpgradeDescription(const std::string& title, const std::string& description) {
    this->title = title;
    this->description = description;

    sprite = new Sprite("Resources/UI.png");

    MoveTo(game->viewport.left + window->CenterX(), game->viewport.top + window->CenterY() + 120.0f);

    upgradeId = -1;
}

UpgradeDescription::~UpgradeDescription() {
    delete sprite;
}

void UpgradeDescription::Update() {
    if (!MinutesTillDawn::upgrading) {
        MinutesTillDawn::scene->Remove(this, STATIC);
        return;
    }
    
    if (upgradeId != MinutesTillDawn::upgradeClick) {
        upgradeId = MinutesTillDawn::upgradeClick;

        int upgradeIdConv = MinutesTillDawn::upgradesIndexes.at(upgradeId);

        upgrade = Upgrade::GetUpgrade(upgradeIdConv);
        title = upgrade.name;
        description = upgrade.description;
    }
}

void UpgradeDescription::Draw() {
    sprite->Draw(x, y, Layer::ABOVEPFRONT);

    Color textColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    float textX = window->CenterX() - 300;
    float titleY = window->CenterY() + 20.0f;
    float descriptionY = window->CenterY() + 60.0f;

    MinutesTillDawn::font16->Draw(textX, titleY, title.c_str(), textColor, 0.0f, 1.0f);
    MinutesTillDawn::font16->Draw(textX, descriptionY, description.c_str(), textColor, 0.0f, 0.8f);

}