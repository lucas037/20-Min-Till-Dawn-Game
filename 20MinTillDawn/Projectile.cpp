#include "Projectile.h"
#include "MinutesTillDawn.h"

Projectile::Projectile(float x, float y, float speedMag, float angle) {
    sprite = new Sprite("Resources/Projectile.png");
    MoveTo(x, y);

    speed = new Vector(XMConvertToDegrees(angle), speedMag);
}

Projectile::~Projectile() {
}

void Projectile::Move(Vector&& v) {
}

void Projectile::Update() {
    Translate(speed->XComponent() * gameTime, speed->YComponent() * gameTime);

    if (X() < game->viewport.left || X() > game->viewport.right || Y() < game->viewport.top || Y() > game->viewport.bottom) {
        MinutesTillDawn::scene->Delete(this, MOVING);
    }
}

void Projectile::Draw() {
    sprite->Draw(x, y, Layer::UPPER);
}
