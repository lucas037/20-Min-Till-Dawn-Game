#include "RepulsionArea.h"
#include "MinutesTillDawn.h"

RepulsionArea::RepulsionArea(float x, float y)
{
	BBox(new Rect(-100, -100, 100, 100));
	type = REPULSION_AREA;

	MoveTo(x, y);

	this->character = nullptr;

	timeCounter = 0.0f;
	duration = 0.5f;
	intensity = 3000.0f;
}

RepulsionArea::RepulsionArea(Character* character)
{
	BBox(new Rect(-100, -100, 100, 100));
	type = REPULSION_AREA;

	MoveTo(character->X(), character->Y());

	this->character = character;

	timeCounter = 0.0f;
	duration = 0.5f;
	intensity = 3000.0f;
}

void RepulsionArea::Update()
{
	if (character != nullptr) {
		MoveTo(character->X(), character->Y());
	}

	timeCounter += gameTime;
	if (timeCounter >= duration) {
		MinutesTillDawn::scene->Delete(this, MOVING);
	}
}

void RepulsionArea::Draw() {}

RepulsionArea::~RepulsionArea() {}