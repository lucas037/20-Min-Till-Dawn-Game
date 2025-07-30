#include "Experience.h"
#include "MinutesTillDawn.h"
#include "AtractionArea.h"

Experience::Experience(uint posX, uint posY)
{
	tile = new TileSet("Resources/xp.png", 8, 8, 2, 4);
	anim = new Animation(tile, 0.160f, true);

	uint active[4] = { 0, 1, 2, 3 };
	anim->Add(0, active, 4);

	this->posX = posX;
	this->posY = posY;

	MoveTo(posX, posY);

	type = EXPERIENCE;

	character = nullptr;

	BBox(new Circle(125.0f));

	speedV = new Vector(0, 0);
	speed = 20.0f;
}

void Experience::Update()
{
	if (character != nullptr) {
		float dx = character->X() - X();
		float dy = character->Y() - Y();

		float magnitude = sqrtf(dx * dx + dy * dy);
		if (magnitude > 1.0f) {
			dx /= magnitude;
			dy /= magnitude;
		}

		float angle = atan2f(dy, dx) * (180.0f / 3.14159265f);
		if (angle < 0.0f) angle += 360.0f;

		speed += 80 * gameTime;

		speedV->RotateTo(angle);
		speedV->ScaleTo(speed);

		Translate(speedV->XComponent() * gameTime, speedV->YComponent() * gameTime);
	}

	anim->NextFrame();
}

void Experience::OnCollision(Object* obj)
{
	if (obj->Type() == ATTRACTION_AREA)
	{
		AttractionArea* area = static_cast<AttractionArea*>(obj);
		if (area->character != nullptr && this->character == nullptr)
		{
			character = area->character;
			speed = area->AttractionForce();

			speedV->ScaleTo(speed);
		}
	}
}

void Experience::Draw()
{
	anim->Draw(x, y, z);
}

Experience::~Experience()
{
	delete tile;
	delete anim;
}