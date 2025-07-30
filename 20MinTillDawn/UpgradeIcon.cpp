#include "UpgradeIcon.h"
#include "MinutesTillDawn.h"

UpgradeIcon::UpgradeIcon(float x, float y, int pos) {
    sprite = new Sprite("Resources/Upgrade_Border.png");
    MoveTo(x, y);

    tileset = new TileSet("Resources/Upgrade_Icons.png", 100, 100, 12, 108);
    anim = new Animation(tileset, 0.120f, true);

    int newPos = pos;
    uint only[1] = { newPos };

    anim->Add(1, only, 1);
    anim->Select(1);

    anim->NextFrame();

    BBox(new Rect(-50, -50, 50, 50));

    activeTimer->Reset();
    Scale(0.8);
    reductSize = true;
}

UpgradeIcon::~UpgradeIcon() {
    delete sprite;
}

void UpgradeIcon::Update() {
    if (!MinutesTillDawn::upgrading) {
        MinutesTillDawn::scene->Remove(this, STATIC);
        return;
    }

    if (!reductSize && activeTimer->Elapsed() > 0.05f) {
        Scale(0.8);
        reductSize = true;
    }
}

void UpgradeIcon::OnCollision(Object* obj) {
    bool confirmPress = false;

    if (MinutesTillDawn::xboxOn) {
        if (MinutesTillDawn::controller->XboxButton(ButtonA)) {
            confirmPress = true;
        }
    }

    bool lButton = window->KeyPress(VK_LBUTTON);
    bool rButton = window->KeyPress(VK_RBUTTON);

    confirmPress = rButton || confirmPress;

    if (obj->Type() == AIM) {
        for (int i = 0; i < 5; i++) {
            if (X() == MinutesTillDawn::upIcons[i]->X()) {
                MinutesTillDawn::upgradeClick = i;

                if (confirmPress) {
                    MinutesTillDawn::upgradeFinishing = true;
                }
            }
        }
    }

    else if (obj->Type() == AIM && window->KeyPress(VK_RBUTTON)) {
        for (int i = 0; i < 5; i++) {
            if (X() == MinutesTillDawn::upIcons[i]->X()) {
                MinutesTillDawn::upgradeClick = i;
            }
        }
    }

    else if (obj->Type() == AIM) {
        if (reductSize) {
            Scale(1.25);
            reductSize = false;
        }

        activeTimer->Reset();
    }
}

void UpgradeIcon::Draw() {
    sprite->Draw(x, y, Layer::ABOVEPBACK, Scale());
    anim->Draw(x, y, Layer::ABOVEPMIDDLE, Scale());
}
