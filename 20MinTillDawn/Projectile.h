#include "Object.h"
#include "Vector.h"
#include "Animation.h"

class Projectile : public Object {
private:
	Animation* anim;          // sprite do proj�til
	Vector* speed;            // velocidade do proj�til

	float rotation;

public:
	Projectile(float x, float y, float angle, float rotation, string newProjectileSprite);
	~Projectile();

	void Move(Vector&& v);
	void Update() override;
	void Draw() override { anim->Draw(X(), Y(), Layer::FRONT, 1.0f, rotation); };
};
