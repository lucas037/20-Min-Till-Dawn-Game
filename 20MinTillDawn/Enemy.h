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
public:
	Sprite* spriteL = nullptr;
	Sprite* spriteR = nullptr;
	Sprite* spriteT = nullptr;
	Sprite* spriteB = nullptr;

	Enemy();
	~Enemy();

	void Move(Vector&& v);
	void Update();
	void Draw();

	void UpdateSprite(Sprite* newSprite);
};