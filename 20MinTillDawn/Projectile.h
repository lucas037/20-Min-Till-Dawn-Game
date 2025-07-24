#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Object.h"
#include "Vector.h"
#include "Sprite.h"

class Projectile : public Object {
private:
	Sprite* sprite;
	Vector* speed;
public:
	bool show = true;
	Projectile(float x, float y, float speedMag, float angle);
	~Projectile();

	void Move(Vector&& v);
	void Update();
	void Draw();
	void OnCollision(Object* obj);

};
#endif