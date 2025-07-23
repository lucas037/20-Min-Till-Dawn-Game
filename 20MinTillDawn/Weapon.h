#include "Object.h"
#include "Animation.h"
#include "Vector.h"
#include "Character.h"

enum AnimationDirection { RIGHTRELOAD, LEFTRELOAD };

class Weapon : public Object
{
private:
	Animation* anim;
	string projectileSprite;

	Character* character;
	Vector* direction;

	float x, y, rotation;
	bool show = true;

public:
	Weapon(Character* character, string newSprite, string newProjectileSprite);
	~Weapon();

	void Move(Vector&& v);
	void Update();
	void Draw() {
		if (show)
			anim->Draw(x, y, Layer::FRONT, 1.0f, rotation); 
	};

	void ChangeMouseMode(bool newShow) {
		show = newShow;
	}
};