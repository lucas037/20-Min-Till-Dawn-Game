#include "Projectile.h"
#include "TileSet.h"

Projectile::Projectile(float angle, string newProjectileSprite) {
	TileSet tileSet = TileSet(newProjectileSprite, 32, 32, 1, 1);


}

Projectile::~Projectile() {
	delete sprite;
}

void Projectile::Update()
{

}
