#include "Object.h"
#include "Animation.h"
#include "Vector.h"
#include "Player.h"

class Weapon : public Object
{
private:
	Animation* anim;
	string projectileSprite;

	float x, y, rotation;

public:
	Weapon(Player* player, string newSprite, string newProjectileSprite);
	~Weapon();

	void Move(Vector&& v);
	void Update();
	void Draw();
};
