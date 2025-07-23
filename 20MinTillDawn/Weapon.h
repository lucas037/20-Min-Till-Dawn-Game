#include "Object.h"
#include "Animation.h"
#include "Vector.h"
#include "Character.h"
#include "Player.h"

#ifndef WEAPON_H
#define WEAPON_H

enum AnimationDirection { RIGHTRELOAD, LEFTRELOAD };

class Weapon : public Object
{
private:
	Animation* anim;
	string projectileSprite;

	float x, y, rotation;
	float aimX, aimY;

	float shotDelay;	// delay between shots
	float ammo;			// current ammo count
	float maxAmmo;		// maximum ammo count

public:
	Weapon(Character* newCharacter, string newSprite, string newProjectileSprite);
	~Weapon();

	void Move(Vector&& v);
	void Move(float x, float y) {
		aimX = x;
		aimY = y;
	}
	void Update();
	void Draw() {
		anim->Draw(x, y, Layer::FRONT, 1.0f, rotation); 
	};

	float ShotDelay() { return shotDelay; }
	void ShotDelay(float newShotDelay) { shotDelay = newShotDelay; }
	float Ammo() { return ammo; }
	void Ammo(float newAmmo) { ammo = newAmmo; }

};

#endif // WEAPON_H