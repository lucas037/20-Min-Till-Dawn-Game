#include "Object.h"
#include "Vector.h"
#include "Sprite.h"

class Enemy: public Object {
private:
	Sprite* sprite;
public:
	Enemy(float posX, float posY, Sprite * newSprite);
	~Enemy();

	void Move(Vector&& v);
	void Update();
	void Draw();
};