#include "Aim.h"

Aim::Aim(float x, float y) {
    sprite = new Sprite("Resources/Aim.png");
    MoveTo(x, y);
}

Aim::~Aim() {
}

void Aim::Move(Vector&& v) {
}

void Aim::Update() {
}

void Aim::Draw() {
    if (show)
        sprite->Draw(x, y, Layer::FRONT);
}
