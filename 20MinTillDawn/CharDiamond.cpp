#include "CharDiamond.h"
#include "AtractionArea.h"
#include "Shadow.h"

CharDiamond::CharDiamond()
{
	tileset = new TileSet("Resources/Player_Diamond.png", 64, 58, 8, 24);
	anim = new Animation(tileset, 0.120f, true);

	uint stop[6] = { 0, 1, 2, 3, 4, 5 };
	uint running[4] = { 8, 9, 10 , 11 };
	uint walking[8] = { 16, 17, 18, 19, 20, 21, 22, 23 };

	anim->Add(STOP, stop, 6);
	anim->Add(RUNNIG, running, 4);
	anim->Add(WALKING, walking, 8);

	speed = new Vector(0, 0);

	BBox(new Rect(-18, -18, 16, 26));

	lifePoints = 7;
	maxLifePoints = 7;

	StartHearts();

	shootingSpeed = 10.0f;
	normalSpeed = 15.0f;

	maxSpeed = normalSpeed;

	AttractionArea* attractionArea = new AttractionArea(this);
	MinutesTillDawn::scene->Add(attractionArea, MOVING);

	Shadow* shadow = new Shadow(this);
	MinutesTillDawn::scene->Add(shadow, STATIC);
}

CharDiamond::~CharDiamond()
{
	if (particles != nullptr) {
		delete particles;
	}

	if (tileset != nullptr) {
		delete tileset;
	}

	if (anim != nullptr) {
		delete anim;
	}

	if (speed != nullptr) {
		delete speed;
	}
}

void CharDiamond::OnCollision(Object* obj)
{
	Character::OnCollision(obj);
}

void CharDiamond::Update()
{
	if (MinutesTillDawn::upgrading)
		return;

	Character::Update();

	if (speed->Magnitude() > 0.0f && speed->Magnitude() < 15.0f) {
		anim->Select(WALKING);
	}
	else if (speed->Magnitude() >= 15.0f) {
		anim->Select(RUNNIG);
	}
	else {
		anim->Select(STOP);
	}
	anim->NextFrame();
}