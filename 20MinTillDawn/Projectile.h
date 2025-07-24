#include "Object.h"
#include "Vector.h"
#include "Animation.h"

class Projectile : public Object {
private:
	Animation* anim;          // sprite do proj�til
	Vector* speed;            // velocidade do proj�til

	float rotation;
	bool flipped = false;
	bool projectile = false;

public:
	Projectile(float x, float y, float angle, float rotation, string newProjectileSprite);
	~Projectile();

	void Move(Vector&& v);
	//void OnCollision(Object* obj) override;
	void Update() override;
	void Draw() override { anim->Draw(X(), Y(), Layer::FRONT, 1.0f, rotation); };
};
