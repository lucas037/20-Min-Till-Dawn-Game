#include "Laser.h"

Laser::Laser() {
	tileset = new TileSet("Resources/ShoggothLaser.png", 64, 1216, 7, 7);
	anim = new Animation(tileset, 0.180f, false);

	uint prep[1] = { 0 };
	uint firing[6] = { 1, 2, 3, 4, 5, 6 };

	anim->Add(0, prep, 1);
	anim->Add(1, firing, 6);
	anim->Add(1, firing, 6);

	anim->Select(0);

	float centerX = X();
	float centerY = Y();

	float radius = 192.0f;

	float xPlayer = MinutesTillDawn::player->X();
	float yPlayer = MinutesTillDawn::player->Y();

	float dx = xPlayer - centerX;
	float dy = yPlayer - centerY;

	float angle = atan2f(dy, dx);

	laserX = centerX + (radius / 2) * cosf(angle);
	laserY = centerY + (radius / 2) * sinf(angle);

	rotation = XMConvertToDegrees(angle);
}

void Laser::Update() {

	if (anim != nullptr) {
		anim->NextFrame();
	}


}