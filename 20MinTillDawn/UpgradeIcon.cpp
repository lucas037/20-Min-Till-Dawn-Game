#include "UpgradeIcon.h"
#include "MinutesTillDawn.h"

UpgradeIcon::UpgradeIcon(Sprite* sprite, float x, float y) {
    this->sprite = sprite;
    MoveTo(x, y);

    BBox(new Rect(-50, -50, 50, 50));

    activeTimer->Reset();
    Scale(0.8);
    reductSize = true;
}

UpgradeIcon::~UpgradeIcon() {
    delete sprite;
}

void UpgradeIcon::Update() {
    if (!reductSize && activeTimer->Elapsed() > 0.05f) {
        Scale(0.8);
        reductSize = true;
    }
}

void UpgradeIcon::OnCollision(Object* obj) {
    if (obj->Type() == AIM && window->KeyPress(VK_LBUTTON)) {
        exit(0);
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
    sprite->Draw(X(), Y(), Layer::ABOVEPMIDDLE, Scale());
}
