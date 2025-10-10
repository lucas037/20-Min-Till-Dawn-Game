#include "AtractionArea.h"
#include "MinutesTillDawn.h"

AttractionArea::AttractionArea(Character* character)
{
	this->character = character;
	width = 50.0f; 
	attractionForce = 100.0f;
	BBox(new Circle(width));

	type = ATTRACTION_AREA;
}

void AttractionArea::Draw() {}

float AttractionArea::AttractionForce()
{
	return attractionForce;
}

void AttractionArea::Update()
{
	if (character == nullptr) return;

	MoveTo(character->X(), character->Y());
}

