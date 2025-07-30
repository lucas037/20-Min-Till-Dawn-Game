#pragma once

#pragma once
#include "Object.h"
#include "Animation.h"
#include "Character.h"

class Shadow : public Object
{
private:
	TileSet* tile;
	Animation* anim;

public:
	uint posX;
	uint posY;

	Character* character;

	Shadow(Character* character);
	~Shadow();

	void Draw();
	void Update();
};
