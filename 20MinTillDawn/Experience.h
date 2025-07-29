#pragma once
#include "Object.h"
#include "Animation.h"
#include "Character.h"

class Experience : public Object
{
private:
	TileSet* tile;
	Animation* anim;
	Character* character;
	Vector* speedV = nullptr;

public:
	uint posX;
	uint posY;
	float speed;

	Experience(uint posX, uint posY);
	~Experience();

	void Draw();
	void Update();
	void OnCollision(Object* obj);
};