#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Object.h"
#include "Vector.h"
#include "Animation.h"

enum AnimationID {
	FIRING,
	BULLET,
	HIT
};

class Projectile : public Object {
private:
	Animation* anim;
	Vector* speed;

	float rotation; // rotação do projétil
	bool firing; // indica se o projétil está disparando
	bool hitting; // indica se o projétil está colidindo

public:
	bool show = true;
	Projectile(float x, float y, float speedMag, float angle);
	~Projectile();

	void Update();
	void Draw();
	void OnCollision(Object* obj);

};
#endif