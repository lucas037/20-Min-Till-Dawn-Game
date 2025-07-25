#include "RepulsionArea.h"
#include "MinutesTillDawn.h"

RepulsionArea::RepulsionArea(float x, float y)
{
	type = REPULSION_AREA;

	MoveTo(x, y);

	this->character = nullptr;

	timeCounter = 0.0f;
	duration = 0.3f;
	intensity = 5000.0f;

	maxHalfWidth = 100.0f;
	maxHalfHeight = 100.0f;

	float initialHalfWidth = maxHalfWidth / 4.0f;
	float initialHalfHeight = maxHalfHeight / 4.0f;
	BBox(new Rect(-initialHalfWidth, -initialHalfHeight, initialHalfWidth, initialHalfHeight));
}

RepulsionArea::RepulsionArea(Character* character)
{
	type = REPULSION_AREA;

	MoveTo(character->X(), character->Y());

	this->character = character;

	timeCounter = 0.0f;
	duration = 0.3f;
	intensity = 5000.0f;

	maxHalfWidth = 150.0f;
	maxHalfHeight = 150.0f;

	float initialHalfWidth = maxHalfWidth / 4.0f;
	float initialHalfHeight = maxHalfHeight / 4.0f;
	BBox(new Rect(-initialHalfWidth, -initialHalfHeight, initialHalfWidth, initialHalfHeight));
}

void RepulsionArea::Update()
{
	if (character != nullptr) {
		MoveTo(character->X(), character->Y());
	}

	timeCounter += gameTime;

	float progress = 1.0f < (timeCounter / duration) ? 1.0f : (timeCounter / duration) ;

	float initialHalfWidth = maxHalfWidth / 4.0f;
	float currentHalfWidth = initialHalfWidth + (maxHalfWidth - initialHalfWidth) * progress;

	float initialHalfHeight = maxHalfHeight / 4.0f;
	float currentHalfHeight = initialHalfHeight + (maxHalfHeight - initialHalfHeight) * progress;

	
	BBox(new Rect(-currentHalfWidth, -currentHalfHeight, currentHalfWidth, currentHalfHeight));

	if (timeCounter >= duration) {
		MinutesTillDawn::scene->Delete(this, MOVING);
	}
}

void RepulsionArea::Draw() {}

RepulsionArea::~RepulsionArea() {}