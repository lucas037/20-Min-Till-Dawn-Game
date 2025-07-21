#include "RepulsionArea.h"
#include "GeoWars.h"

RepulsionArea::RepulsionArea(float x, float y)
{
	BBox(new Rect(-100, -100, 100, 100));
	type = REPULSION_AREA;

	MoveTo(x, y);

	timeCounter = 0.0f;
	duration = 0.5f;
	intensity = 3000.0f;
}

void RepulsionArea::Update()
{
	timeCounter += gameTime;
	if (timeCounter >= duration) {
		GeoWars::scene->Delete(this, MOVING);
	}
}

void RepulsionArea::Draw() {}

RepulsionArea::~RepulsionArea() {}