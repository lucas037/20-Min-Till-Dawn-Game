#include "Enemy.h"
#include "Aleatory.h"
#include "MinutesTillDawn.h"
#include "RepulsionArea.h"
#include "Config.h"

Enemy::Enemy() {
	id = MinutesTillDawn::newEnemyId;
	MinutesTillDawn::newEnemyId += 1;
	life = 0.0f;
	speed = new Vector(0, 0);

	int positionDirection = Aleatory::randrange(0, 4);
	float zeroToOneNumber = (Aleatory::randrange(0, 101)) / 100.0;
	float screenDistanceSpawn = 200.0;
	float randomPosition = 0.0;

	switch (positionDirection) {

	case ENEMY_UP:
		randomPosition = (zeroToOneNumber * window->Width());
		MoveTo(game->viewport.left + randomPosition, game->viewport.top - screenDistanceSpawn);
		break;
	case ENEMY_DOWN:
		randomPosition = (zeroToOneNumber * window->Width());
		MoveTo(game->viewport.left + randomPosition, game->viewport.bottom + screenDistanceSpawn);
		break;
	case ENEMY_LEFT:
		randomPosition = (zeroToOneNumber * window->Height());
		MoveTo(game->viewport.left - screenDistanceSpawn, game->viewport.top + randomPosition);
		break;
	case ENEMY_RIGHT:
		randomPosition = (zeroToOneNumber * window->Height());
		MoveTo(game->viewport.right + screenDistanceSpawn, game->viewport.top + randomPosition);
		break;

	}

	type = ENEMY;
}

Enemy::~Enemy() {
	if (speed != nullptr) {
		delete speed;
	}
}

void Enemy::Move(Vector&& v)
{
}

void Enemy::OnCollision(Object* obj) {
	if (obj->Type() == ENEMY) {
		float dx = x - obj->X();
		float dy = y - obj->Y();

		float length = sqrt(dx * dx + dy * dy);
		if (length == 0.0f) {
			length = 0.0001f;
		}

		dx /= length;
		dy /= length;

		float separationForce = 150.0f;

		float separationAngle = atan2f(dy, dx) * (180.0f / 3.14159265f);
		if (separationAngle < 0.0f) {
			separationAngle += 360.0f;
		}

		Vector separationVector(separationAngle, separationForce * gameTime);
		speed->Add(separationVector);
	}

	if (obj->Type() == PROJECTILE) {
		TakeDamage(Config::shotDamage);
	}

	if (obj->Type() == REPULSION_AREA) {
		RepulsionArea* repulsion = dynamic_cast<RepulsionArea*>(obj);

		if (repulsion != nullptr) {
			float intensity = repulsion->Intensity();

			float dx = x - repulsion->X();
			float dy = y - repulsion->Y();

			float length = sqrt(dx * dx + dy * dy);
			if (length == 0.0f) length = 0.0001f;

			dx /= length;
			dy /= length;

			float repulsionAngle = atan2f(dy, dx) * (180.0f / 3.14159265f);
			if (repulsionAngle < 0.0f) repulsionAngle += 360.0f;

			Vector repulsionVector(repulsionAngle, intensity * gameTime);

			speed->Add(repulsionVector);

			inRepulsion = true;
		}
	}

}

// -------------------------------------------------------------------------------

void Enemy::Update()
{
	if (MinutesTillDawn::upgrading) {
		return;
	}

	float xPlayer = MinutesTillDawn::player->X();
	float yPlayer = MinutesTillDawn::player->Y();
	float xEnemy = X();
	float yEnemy = Y();

	float dx = xPlayer - xEnemy;
	float dy = yPlayer - yEnemy;

	UpdateMovement(dx, dy);
	float maxSpeed = 100.0f;
	if (speed->Magnitude() > maxSpeed && !inRepulsion) {
		speed->ScaleTo(maxSpeed);
	}

	Translate(speed->XComponent() * gameTime, speed->YComponent() * gameTime);

	if (dx >= 0 && !lookRight) {
		if (anim != nullptr) {
			anim->FlipX();
		}

		if (spriteR != nullptr) {
			sprite = spriteR;
		}

		lookRight = true;
	}
	else if (dx < 0 && lookRight) {
		if (anim != nullptr) {
			anim->FlipX();
		}

		if (spriteL != nullptr) {
			sprite = spriteL;
		}

		lookRight = false;
	}

	if (anim != nullptr)
		anim->NextFrame();

	inRepulsion = false;
}

// -------------------------------------------------------------------------------

void Enemy::Draw() {
	if (anim != nullptr)
		anim->Draw(x, y, Layer::MIDDLE);
	else if (sprite != nullptr)
		sprite->Draw(x, y, Layer::MIDDLE);
}

// M�todos auxiliares
void Enemy::UpdateMovement(float dx, float dy) {
	float magnitude = sqrtf(dx * dx + dy * dy);
	if (magnitude > 1.0f) {
		dx /= magnitude;
		dy /= magnitude;
	}

	float angle = atan2f(dy, dx) * (180.0f / 3.14159265f);
	if (angle < 0.0f) angle += 360.0f;

	Vector attractionVector(angle, 100.0f * gameTime);
	speed->Add(attractionVector);
}

// -------------------------------------------------------------------------------

void Enemy::UpdateSprite(Sprite * newSprite) {
	sprite = newSprite;
}

void Enemy::TakeDamage(float damage) {
	life -= damage;

	if (life < 0.0) {
		MinutesTillDawn::player->AddEnemyKilled();
		MinutesTillDawn::scene->Delete(this, MOVING);
		
		for (int i = 0; i < MinutesTillDawn::enemies.size(); ++i) {
			if (MinutesTillDawn::enemies[i]->id == id) {
				MinutesTillDawn::enemies.erase(MinutesTillDawn::enemies.begin() + i);
				break;
			}
		}

	}
}