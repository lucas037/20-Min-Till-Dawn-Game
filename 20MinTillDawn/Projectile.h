#include "Object.h"
#include "Vector.h"
#include "Animation.h"

class Projectile : public Object {
private:
	Animation* anim;          // sprite do projétil
	Vector* speed;            // velocidade do projétil

	float rotation;

public:
	Projectile(float x, float y, float angle, float rotation, string newProjectileSprite);
	~Projectile();

	void Move(Vector&& v);
	void Update() override;
	void Draw() override { anim->Draw(X(), Y(), Layer::FRONT, 1.0f, rotation); };
};
