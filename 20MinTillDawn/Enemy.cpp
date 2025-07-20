#include "Enemy.h"
#include "Aleatory.h"
#include "GeoWars.h"-

Enemy::Enemy() {
	float initPosX = game->CenterX();
	float initPosY = game->CenterY();
	int positionDirection = Aleatory::randrange(0, 4);
	float auxNumBetween1s = (Aleatory::randrange(0, 201) - 100.0) / 100;

	switch (positionDirection) {
		case ENEMY_UP:
			initPosY += (-window->Height() / 2);
			initPosX += (auxNumBetween1s * window->Width() / 2);
			break;
		case ENEMY_DOWN:
			initPosY += (window->Height() / 2);
			initPosX += (auxNumBetween1s * window->Width() / 2);
			break;
		case ENEMY_LEFT:
			initPosX += (-window->Width() / 2);
			initPosY += (auxNumBetween1s * window->Height() / 2);
			break;
		case ENEMY_RIGHT:
			initPosX += (window->Width() / 2);
			initPosY += (auxNumBetween1s * window->Height() / 2);
			break;

	}

	MoveTo(initPosX, initPosY);

	type = ENEMY;
}

Enemy::~Enemy() {

}

void Enemy::Move(Vector&& v)
{
}

// -------------------------------------------------------------------------------

void Enemy::Update()
{
	float xPlayer = GeoWars::player->X();
	float yPlayer = GeoWars::player->Y();
	float xEnemy = X();
	float yEnemy = Y();

	float distX = xPlayer - xEnemy;
	float distY = yPlayer - yEnemy;

	float angleRad = atan2(distY, distX);
	float angle = angleRad * (180.0f / 3.14159265f);
	Vector v(angle, 100.0f);

	Translate(v.XComponent() * gameTime, v.YComponent() * gameTime);

	if (v.XComponent() > 0 && spriteR != nullptr) {
		sprite = spriteR;
	}
	else if (v.XComponent() < 0 && spriteL != nullptr) {
		sprite = spriteL;
	}

	if (v.YComponent() > 0 && spriteB != nullptr) {
		sprite = spriteB;
	}
	else if (v.YComponent() < 0 && spriteT != nullptr) {
		sprite = spriteT;
	}
}

// -------------------------------------------------------------------------------

void Enemy::Draw() {
	sprite->Draw(x, y, Layer::MIDDLE);
	int k = 2;
}

// -------------------------------------------------------------------------------

void Enemy::UpdateSprite(Sprite * newSprite) {
	sprite = newSprite;
}