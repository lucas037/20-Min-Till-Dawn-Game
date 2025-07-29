#include "Laser.h"
#include "MinutesTillDawn.h"

Laser::Laser(float Sx, float Sy) {
	timer = new Timer();
	timer->Start();

	sX = Sx;
	sY = Sy;

	tileset = new TileSet("Resources/ShoggothLaser.png", 1216, 64, 1, 7);
	anim = new Animation(tileset, 0.140f, false);

	uint prep[1] = { 0 };
	uint firing[6] = { 1, 2, 3, 4, 5, 6 };

	anim->Add(0, prep, 1);
	anim->Add(1, firing, 6);

	anim->Select(0);
	Laser::firing = false;
}

Laser::~Laser() {
	delete tileset;
	delete anim;
	delete timer;
}

void Laser::Update() {
	if (MinutesTillDawn::upgrading) {
		return;
	}
	
	if (timer->Elapsed() < 0.8f && !Laser::firing) {
		FollowPlayer();
	}
	else if (timer->Elapsed() >= 1.0f && !Laser::firing) {

		firing = true;
		anim->Select(1);
		timer->Reset();
	} else if (timer->Elapsed() >= 0.84f  && Laser::firing && anim->Inactive()) {

		MinutesTillDawn::scene->Delete(this, STATIC);
	}

	if (anim != nullptr) {
		anim->NextFrame();
	}
}

void Laser::FollowPlayer() {
	float centerX = sX;
	float centerY = sY;

	float radius = 96 + 608 - 18 - 13;

	float xPlayer = MinutesTillDawn::player->X();
	float yPlayer = MinutesTillDawn::player->Y();

	float dx = xPlayer - centerX;
	float dy = yPlayer - centerY;

	float angle = atan2f(dy, dx);

	x = centerX + radius * cosf(angle);
	y = centerY + radius * sinf(angle);

	MoveTo(x, y);

	rotation = XMConvertToDegrees(angle);
}