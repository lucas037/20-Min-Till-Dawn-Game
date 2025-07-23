#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include "Vector.h"
#include "Sprite.h"

enum EnemyPosition {
	ENEMY_UP,
	ENEMY_DOWN,
	ENEMY_LEFT,
	ENEMY_RIGHT
};


class Enemy: public Object {
private:
	Sprite* sprite;

protected:
	Vector* speed;
public:
	Sprite* spriteL = nullptr;
	Sprite* spriteR = nullptr;
	Sprite* spriteT = nullptr;
	Sprite* spriteB = nullptr;
	float life;
	int id;

	Enemy();
	~Enemy();

	void Move(Vector&& v);
	void Update();
	void Draw();

	void OnCollision(Object* obj);

	void UpdateSprite(Sprite* newSprite);
	void UpdateMovement(float dx, float dy);

	Vector* Speed() { return speed; }

	void TakeDamage(float damage);
};

#endif