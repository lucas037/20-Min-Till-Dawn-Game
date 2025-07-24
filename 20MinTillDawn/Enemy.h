#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include "Vector.h"
#include "Sprite.h"
#include "Animation.h"

enum EnemyPosition {
	ENEMY_UP,
	ENEMY_DOWN,
	ENEMY_LEFT,
	ENEMY_RIGHT
};


class Enemy: public Object {
private:

protected:
	Vector* speed;
public:
	Sprite* spriteR = nullptr;
	Sprite* spriteL = nullptr;
	float life;
	int id;
	TileSet* tileset;
	Animation* anim;
	bool lookRight = true;
	Sprite* sprite;

	Enemy();
	~Enemy();

	void Move(Vector&& v);
	void Update();
	void Draw();
	void Finalize() {
		delete tileset;
		delete anim;
		delete sprite;
		delete spriteR;
		delete spriteL;
		delete speed;
	}

	void OnCollision(Object* obj);

	void UpdateSprite(Sprite* newSprite);
	void UpdateMovement(float dx, float dy);

	Vector* Speed() { return speed; }

	void TakeDamage(float damage);
};

#endif