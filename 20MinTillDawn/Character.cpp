#include "Character.h"
#include "MinutesTillDawn.h"
#include "RepulsionArea.h"
#include "BloodParticles.h"
#include "Aleatory.h"
#include "Config.h"
#include "Shadow.h"

Character::Character()
{
	particles = nullptr;

	maxSpeed = 15.0f;

	MoveTo(game->CenterX(), game->CenterY());

	tileset = nullptr;
	anim = nullptr;

	speed = nullptr;

	right = true;
	lifePoints = 0;
	maxLifePoints = 0;

	isStunned = false;
	stunTimer = 0.0f;

	xpPoints = 0;
	pointsToNextLevel = 1;
	level = 1;
}

void Character::OnCollision(Object* obj)
{
	if (obj->Type() == ENEMY || obj->Type() == LASER) {
		Damage();
	}

	if (obj->Type() == EXPERIENCE) {
		MinutesTillDawn::scene->Delete(obj, MOVING);

		AddExperience();
	}
}

void Character::Update()
{
	if (MinutesTillDawn::upgrading)
		return;

	if (isStunned) {
		stunTimer += gameTime;
		if (stunTimer >= stunDuration) {
			isStunned = false;
		}
	}

	if (isShooting) {
		shootTimer += gameTime;
		if (shootTimer >= shootDuration) {
			shoot(false);
			shootTimer = 0.0f;
		}
	}

	if (walkingSongActive) {
		walkTimer += gameTime;

		if (walkTimer >= walkDuration ) {
			walkingSongActive = false;
		}
	}

	if (isInvincible) {
		timeCounter += gameTime;

		if (timeCounter >= invincibilityTime) {
			isInvincible = false;
			timeCounter = 0.0f;
		}
	}

	if (lifePoints == 1 && !lowHp) {
		MinutesTillDawn::audio->Play(LOW_HP, true);

		lowHp = true;
	}
	else if (lifePoints != 1) {
		MinutesTillDawn::audio->Stop(LOW_HP);
		lowHp = false;
	}

	Move();

	MinutesTillDawn::player->MoveTo(X(), Y());
}

void Character::Draw()
{
	anim->Draw(x, y, Layer::FRONT, Scale());
}

Character::~Character() {}

// ---------------------------------------------------------------------------------
// METODOS AUXILIARES
// ---------------------------------------------------------------------------------
void Character::Move() {
	if (isStunned) {
		speed->ScaleTo(0.0f);
		return;
	}

	float dx = 0.0f;
	float dy = 0.0f;
	float delta = maxSpeed * gameTime;

	HandleXboxInput(dx, dy);
	HandleGenericControllerInput(dx, dy);
	HandleKeyboardInput(dx, dy);

	if (dx == 0.0f && dy == 0.0f) {
		speed->ScaleTo(0.0f);
		return;
	}

	if ((dx != 0 || dy != 0) && !walkingSongActive) {
		MinutesTillDawn::audio->Play(WALK, false);

		walkingSongActive = true;
		walkTimer = 0;
	}

	UpdateAnimationDirection(dx);
	UpdateMovement(dx, dy);

	speed->ScaleTo(maxSpeed);

	Translate(speed->XComponent() * delta, -speed->YComponent() * delta);

	if (X() < 0 || X() > game->Width() || Y() < 0 || Y() > game->Height()) {
		MoveTo(game->CenterX(), game->CenterY());
		Damage();
	}
}

void Character::HandleXboxInput(float& dx, float& dy) {
	const float deadZone = 0.2f;

	if (!MinutesTillDawn::xboxOn)
		return;

	if (!MinutesTillDawn::controller->XboxUpdateState(0)) {
		MinutesTillDawn::xboxOn = false;
		MinutesTillDawn::controllerOn = MinutesTillDawn::controller->UpdateState();
		return;
	}

	MinutesTillDawn::controller->XboxUpdateState();

	float x = MinutesTillDawn::controller->XboxAnalog(ThumbLX);
	float y = MinutesTillDawn::controller->XboxAnalog(ThumbLY);

	if (fabs(x) >= deadZone) dx += x;
	if (fabs(y) >= deadZone) dy += y;
}

void Character::HandleGenericControllerInput(float& dx, float& dy) {
	const float deadZone = 0.2f;

	if (!MinutesTillDawn::controllerOn)
		return;

	if (!MinutesTillDawn::controller->UpdateState()) {
		MinutesTillDawn::controllerOn = false;
		MinutesTillDawn::xboxOn = MinutesTillDawn::controller->XboxInitialize(0);
		return;
	}

	float x = MinutesTillDawn::controller->Axis(AxisX);
	float y = MinutesTillDawn::controller->Axis(AxisY);

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

void Character::StartHearts()
{
	Heart* heart;

	for (uint i = 0; i < maxLifePoints; i++) {
		heart = new Heart(50 * (i + 1), 40);
		hearts.push_back(heart);
		MinutesTillDawn::scene->Add(heart, STATIC);
	}

	if (lifePoints < maxLifePoints) {
		for (uint i = lifePoints; i < maxLifePoints; i++) {
			if (i < hearts.size()) {

				hearts[i]->SetInactive();
			}
		}
	}
}

void Character::shoot(bool shooting)
{
	isShooting = shooting;

	if (isShooting) {
		shootTimer = 0.0f;
	}

	maxSpeed = shooting ? shootingSpeed : normalSpeed;
}

void Character::Damage()
{
	if (isInvincible || lifePoints <= 0) return;

	float lucky = Aleatory::randrange(0, 1000) / 1000.0f;
	if (lucky < Config::dodgeChance) {
		MinutesTillDawn::scene->Add(new RepulsionArea(this), MOVING);
		return;
	}

	lifePoints--;

	MinutesTillDawn::scene->Add(new BloodParticles(x, y), STATIC);

	MinutesTillDawn::scene->Add(new RepulsionArea(this), MOVING);

	MinutesTillDawn::audio->Play(DAMAGE);

	if (lifePoints < maxLifePoints) {
		for (uint i = lifePoints; i < maxLifePoints; i++) {
			if (i < hearts.size()) {

				hearts[i]->SetInactive();
			}
		}
	}

	isInvincible = true;
	timeCounter = 0.0f;

	isStunned = true;
	stunTimer = 0.0f;
}

void Character::AddExperience()
{
	xpPoints++;
	if (xpPoints >= pointsToNextLevel) {
		xpPoints = 0;
		pointsToNextLevel += 10;
		level++;

		MinutesTillDawn::startUpgrade = true;
	}
}

void Character::AddHeart() {
	if (lifePoints < maxLifePoints) {
		hearts[lifePoints]->SetActive();
		lifePoints++;
	}

}

void Character::AddMaxHeart() {

	Heart* heart = new Heart(50 * maxLifePoints, 40);

	if (lifePoints < maxLifePoints) {
		hearts[lifePoints]->SetActive();
		heart->SetInactive();
	}

	hearts.push_back(heart);
	MinutesTillDawn::scene->Add(heart, STATIC);

	maxLifePoints++;
	lifePoints++;

}
