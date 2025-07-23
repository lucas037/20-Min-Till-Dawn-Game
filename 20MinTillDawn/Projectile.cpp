#include "Projectile.h"
#include "TileSet.h"

Projectile::Projectile(float x, float y, float angle, float rotation, string newProjectileSprite) {
	TileSet* tileSet = new TileSet(newProjectileSprite, 1, 1);
	anim = new Animation(tileSet, 0.1f, true);

	uint projectileFrames[1] = { 0 };

	anim->Add(0, projectileFrames, 1);

	anim->Select(0);

	speed = new Vector(XMConvertToDegrees(angle), 100);

	BBox(new Circle(10.0f));

	// Set the rotation of the projectile
	this->rotation = rotation;

	// Define the initial position based on the angle
	MoveTo(x, y);
}

Projectile::~Projectile() {
	delete anim;
}

void Projectile::Update()
{
	Translate(speed->XComponent() * gameTime, speed->YComponent() * gameTime);
}
