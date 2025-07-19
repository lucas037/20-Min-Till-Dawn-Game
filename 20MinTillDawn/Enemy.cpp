#include "Enemy.h"
#include "Aleatory.h"

Enemy::Enemy(Sprite * newSprite) {
	float initPosX = game->CenterX();
	float initPosY = game->CenterY();
	int positionDirection = Aleatory::randrange(2, 4);
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
	sprite = newSprite;
}

Enemy::~Enemy() {

}

void Enemy::Move(Vector&& v)
{
}

// -------------------------------------------------------------------------------

void Enemy::Update()
{
}

// -------------------------------------------------------------------------------

void Enemy::Draw() {
	sprite->Draw(x, y, Layer::MIDDLE);
	int k = 2;
}