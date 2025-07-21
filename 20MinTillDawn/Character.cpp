#include "Character.h"
#include "GeoWars.h"
#include "RepulsionArea.h"

Character::Character()
{
	particles = nullptr;

	MoveTo(game->CenterX(), game->CenterY());

	tileset = new TileSet("Resources/Player_Shana.png", 64, 58, 8, 24);
	anim = new Animation(tileset, 0.120f, true);

	uint stop[6] = { 0, 1, 2, 3, 4, 5 };
	uint running[4] = {8, 9, 10 , 11 };
	uint walking[8] = { 16, 17, 18, 19, 20, 21, 22, 23};

	anim->Add(STOP, stop, 6);
	anim->Add(RUNNIG, running, 4);
	anim->Add(WALKING, walking, 8);

	speed = new Vector(0, 0);

	BBox(new Rect(-18, -18, 16, 26));

	right = true;
	lifePoints = 4;
	maxLifePoints = 4;

	Heart* heart;

	for (int i = 0; i < maxLifePoints; i++) {
		heart = new Heart(50 * (i + 1), 40);
		hearts.push_back(heart);

		GeoWars::scene->Add(heart, STATIC);
	}
}

void Character::OnCollision(Object* obj)
{
	if (obj->Type() == ENEMY) {
		Damage();
	}
}

void Character::Update()
{
	float delta = 100 * gameTime;

	Move();

	if (isInvincible) {
		timeCounter += gameTime;

		if (timeCounter >= invincibilityTime) {
			isInvincible = false;
			timeCounter = 0.0f;
		}
	}

	if (speed->Magnitude() > 0.0f && speed->Magnitude() < 10.0f) {
		anim->Select(WALKING);
	}
	else if (speed->Magnitude() >= 20.0f) {
		anim->Select(RUNNIG);
	}
	else {
		anim->Select(STOP);
	}
	anim->NextFrame();

	Translate(speed->XComponent() * 0.1f * delta, -speed->YComponent() * 0.1f * delta);

	GeoWars::player->MoveTo(X(), Y());
}

// ---------------------------------------------------------------------------------
// METODOS AUXILIARES
// ---------------------------------------------------------------------------------
void Character::Move() {
	float dx = 0.0f;
	float dy = 0.0f;

	HandleXboxInput(dx, dy);
	HandleGenericControllerInput(dx, dy);
	HandleKeyboardInput(dx, dy);

	if (dx == 0.0f && dy == 0.0f) {
		speed->ScaleTo(0.0f);
		return;
	}

	UpdateAnimationDirection(dx);
	UpdateMovement(dx, dy);
}

void Character::HandleXboxInput(float& dx, float& dy) {
	const float deadZone = 0.2f;

	if (!GeoWars::xboxOn)
		return;

	if (!GeoWars::controller->XboxUpdateState(0)) {
		GeoWars::xboxOn = false;
		GeoWars::controllerOn = GeoWars::controller->UpdateState();
		return;
	}

	GeoWars::controller->XboxUpdateState();

	float x = GeoWars::controller->XboxAnalog(ThumbLX);
	float y = GeoWars::controller->XboxAnalog(ThumbLY);

	if (fabs(x) >= deadZone) dx += x;
	if (fabs(y) >= deadZone) dy += y;
}

void Character::HandleGenericControllerInput(float& dx, float& dy) {
	const float deadZone = 0.2f;

	if (!GeoWars::controllerOn)
		return;

	if (!GeoWars::controller->UpdateState()) {
		GeoWars::controllerOn = false;
		GeoWars::xboxOn = GeoWars::controller->XboxInitialize(0);
		return;
	}

	float x = GeoWars::controller->Axis(AxisX);
	float y = GeoWars::controller->Axis(AxisY);

	if (fabs(x) >= deadZone) dx += x;
	if (fabs(y) >= deadZone) dy += y;
}

void Character::HandleKeyboardInput(float& dx, float& dy) {
	if (window->KeyDown('W')) dy += 1.0f;
	if (window->KeyDown('S')) dy -= 1.0f;
	if (window->KeyDown('A')) dx -= 1.0f;
	if (window->KeyDown('D')) dx += 1.0f;
}

void Character::UpdateAnimationDirection(float dx) {
	if (dx < 0 && right) {
		anim->FlipX();
		right = false;
	}
	else if (dx > 0 && !right) {
		anim->FlipX();
		right = true;
	}
}

void Character::UpdateMovement(float dx, float dy) {
	float magnitude = sqrtf(dx * dx + dy * dy);
	if (magnitude > 1.0f) {
		dx /= magnitude;
		dy /= magnitude;
	}

	float angle = atan2f(dy, dx) * (180.0f / 3.14159265f);
	if (angle < 0.0f) angle += 360.0f;

	speed->RotateTo(angle);

	if (speed->Magnitude() < 20.0f) {
		speed->ScaleTo(speed->Magnitude() + 20 * gameTime);
	}
}

void Character::Damage()
{
	if (isInvincible || lifePoints <= 0) return;

	lifePoints--;

	GeoWars::scene->Add(new RepulsionArea(X(), Y()), MOVING);

	if (lifePoints < maxLifePoints) {
		for (uint i = lifePoints; i < maxLifePoints; i++) {
			if (i < hearts.size()) {

				hearts[i]->SetInactive();
			}
		}
	}

	isInvincible = true;
	timeCounter = 0.0f;
}

void Character::Draw()
{
	anim->Draw(x, y, Layer::FRONT);
}

Character::~Character()
{
	delete anim;
	delete tileset;
	if (particles != nullptr) {
		delete particles;
	}
	delete speed;
}