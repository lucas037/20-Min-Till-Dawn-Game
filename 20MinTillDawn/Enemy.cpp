#include "Enemy.h"

Enemy::Enemy(float posX, float posY, Sprite * newSprite) {
	MoveTo(posX, posY);
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