#include "Shadow.h"

Shadow::Shadow(Character* character)
{
	tile = new TileSet("Resources/Shadow.png", 3072, 2160, 1, 1);
	anim = new Animation(tile, 0.120f, true);

	uint active[1] = { 0 };

	anim->Add(0, active, 1);

	this->character = character;
}

void Shadow::Update()
{
	MoveTo(character->X(), character->Y(), Layer::UPPER);

	anim->NextFrame();
}

void Shadow::Draw()
{
	anim->Draw(x, y, z, 1.05f, 0, {1, 1, 1, 0.5});
}

Shadow::~Shadow()
{
	delete tile;
	delete anim;
}