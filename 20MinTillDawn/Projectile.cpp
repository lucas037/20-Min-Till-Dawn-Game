#include "Projectile.h"
#include "TileSet.h"
#include "MinutesTillDawn.h"

enum AnimationState { SHOOTING, PROJECTILE, HITTING };

Projectile::Projectile(float x, float y, float angle, float rotation, string newProjectileSprite) {
	TileSet* tileSet = new TileSet(newProjectileSprite, 2, 4);
	anim = new Animation(tileSet, 0.1f, true);

	uint shootingFrames[1] = { 0 };
	uint projectileFrames[1] = { 2 };
	uint hittingFrames[1] = { 3 };

	anim->Add(SHOOTING, shootingFrames, 1);
	anim->Add(PROJECTILE, projectileFrames, 1);
	anim->Add(HITTING, projectileFrames, 1);

	anim->Select(SHOOTING);

	if (rotation > 90 && rotation < 270 && !flipped)
	{
		anim->FlipX();
		flipped = true;
	}

	speed = new Vector(XMConvertToDegrees(angle), 100.0f);

	BBox(new Circle(10.0f));

	// Set the rotation of the projectile
	this->rotation = rotation;

	// Define the initial position based on the angle
	MoveTo(x, y);

	type =	MISSILE;
}

Projectile::~Projectile() {
	delete anim;
	delete speed;
}

void Projectile::Update()
{
	Translate(speed->XComponent() * gameTime, speed->YComponent() * gameTime);
}

/*
void Projectile::OnCollision(Object* obj)
{
	if (obj->Type() == ENEMY)
	{
		anim->Select(HITTING);
		// Remove the projectile from the scene
		MinutesTillDawn::scene->Remove();
	}
}
*/