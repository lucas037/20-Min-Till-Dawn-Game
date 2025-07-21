#include "Weapon.h"
#include "TileSet.h"

Weapon::Weapon(Player* player, string newSprite, string newProjectileSprite) {
	// 8 pixels a esquerda e 5 abaixo do centro do jogador
	x = player->X() + 8;
	y = player->Y() + 5;

	MoveTo(x, y);

	TileSet* tileSet = new TileSet(newSprite, 32, 32, 5, 5);
	anim = new Animation(tileSet, 0.1f, true);
	projectileSprite = newProjectileSprite;
}

Weapon::~Weapon()
{
	delete anim;
}

void Weapon::Update() {}

void Weapon::Draw()
{
	anim->Draw(x, y, Layer::FRONT, 1.0f, rotation);
}
