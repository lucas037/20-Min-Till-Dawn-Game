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

	float shotDelay = 0.2;	// delay between shots
	float maxAmmo = 6;		// maximum ammo count
	float ammo = maxAmmo;	// current ammo count

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
	void Reloading();

	float ShotDelay() { return shotDelay; }
	void ShotDelay(float newShotDelay) { shotDelay = newShotDelay; }
	float Ammo() { return ammo; }
	void Ammo(float newAmmo) { ammo = newAmmo; }

};

#endif // WEAPON_H