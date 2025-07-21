#pragma once
#include "Object.h"
#include "Animation.h"

enum HeartState {H_ACTIVE, H_HEARTBEAT, H_INACTIVE};

class Heart : public Object
{
private:
	TileSet* tile;
	Animation* anim;
	float timeCounter = 0.0f;
	float switchInterval = 0.5f;

public:
	uint state;
	uint posX;
	uint posY;

	Heart(uint posX, uint posY);
	~Heart();

	void Draw();
	void Update();
	void ChangeState();
	void SetInactive();
};