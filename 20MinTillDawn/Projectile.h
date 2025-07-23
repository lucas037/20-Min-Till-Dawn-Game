#include "Object.h"
#include "Sprite.h"
#include "Vector.h"

class Projectile : public Object {
private:
	Sprite* sprite;          // sprite do projétil
	Vector speed;            // velocidade do projétil

public:
	Projectile(float angle, string newProjectileSprite);
	~Projectile();

	void Move(Vector&& v);
	void Update() override;
	void Draw() override { sprite->Draw(X(), Y(), Layer::FRONT, 1.0f, Rotation()); };
};
