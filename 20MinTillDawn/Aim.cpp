#include "Aim.h"
#include "MinutesTillDawn.h"

Aim::Aim(float x, float y) {
    sprite = new Sprite("Resources/Aim.png");
    MoveTo(x, y);

    type = AIM;
    BBox(new Rect(-10, -10, 10, 10));
}

Aim::~Aim() {
}

void Aim::Move(Vector&& v) {
}

void Aim::Update() {
}

void Aim::Draw() {
    if (show)
        sprite->Draw(x, y, Layer::ABOVEPFRONT);
}
