#include "Heart.h"

Heart::Heart(uint posX, uint posY)
{
	tile = new TileSet("Resources/HeartsSprite.png", 64, 64, 4, 4);
	anim = new Animation(tile, 0.120f, true);

	uint active[1] = { 0 };
	uint heartbeat[2] = { 1, 2 };
	uint inactive[1] = { 3 };

	anim->Add(H_ACTIVE, active, 1);
	anim->Add(H_HEARTBEAT, heartbeat, 2);
	anim->Add(H_INACTIVE, inactive, 1);

	state = H_ACTIVE;
	anim->Select(H_ACTIVE);

	this->posX = posX;
	this->posY = posY;
}

void Heart::Update()
{
	MoveTo(game->viewport.left + posX, game->viewport.top + posY, Layer::FRONT);

	if (state == H_INACTIVE)
		return;

	timeCounter += gameTime;

	if (timeCounter >= switchInterval)
	{
		if (state == H_ACTIVE)
		{
			state = H_HEARTBEAT;
			anim->Select(H_HEARTBEAT);
		}
		else
		{
			state = H_ACTIVE;
			anim->Select(H_ACTIVE);
		}
		timeCounter = 0.0f;
	}

	anim->NextFrame();
}

void Heart::Draw()
{
	anim->Draw(x, y, z);
}

// Métodos auxiliares
void Heart::ChangeState()
{
	if (state != H_INACTIVE)
	{
		state = H_INACTIVE;
		anim->Select(H_INACTIVE);
	}
	else
	{
		state = H_ACTIVE;
		anim->Select(H_ACTIVE);
	}
}

void Heart::SetInactive()
{
	state = H_INACTIVE;
	anim->Select(H_INACTIVE);
}

void Heart::SetActive()
{
	state = H_ACTIVE;
	anim->Select(H_ACTIVE);
}

Heart::~Heart()
{
	delete tile;
	delete anim;
}