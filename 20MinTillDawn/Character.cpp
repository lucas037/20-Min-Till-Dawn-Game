#include "Character.h"
#include "GeoWars.h"

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

void Character::Move() {
	float dx = 0.0f;
	float dy = 0.0f;

	if (window->KeyDown('W')) dy += 1.0f;
	if (window->KeyDown('S')) dy -= 1.0f;  
	if (window->KeyDown('A')) {
		dx -= 1.0f;
		if (right) {
			anim->FlipX();
			right = false;
		}
	}
	if (window->KeyDown('D')) {
		dx += 1.0f;
		if (!right) {
			anim->FlipX();
			right = true;
		}
	}
	if (dx == 0.0f && dy == 0.0f) {
		speed->ScaleTo(0.0f);
		return;
	}

	float angle = atan2f(dy, dx) * (180.0f / 3.14159265f);
	if (angle < 0.0f) angle += 360.0f;

	speed->RotateTo(angle);

	if (speed->Magnitude() < 20.0f) {
		speed->ScaleTo(speed->Magnitude() + 40 * gameTime);
	}
}

void Character::OnCollision(Object* obj)
{
	if (obj->Type() == ENEMY) {
		Damage();
	}
}

void Character::Damage()
{
	if (isInvincible || lifePoints <= 0) return;

	lifePoints--;

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