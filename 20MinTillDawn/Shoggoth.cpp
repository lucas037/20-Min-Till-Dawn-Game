#include "Shoggoth.h"
#include "MinutesTillDawn.h"
#include "Aleatory.h"
#include "Config.h"

Shoggoth::Shoggoth() : Enemy() {
	timer = new Timer();
	timer->Start();
	
	tileset = new TileSet("Resources/BossEnemy_Shoggoth.png", 192, 192, 4, 4);
	anim = new Animation(tileset, 0.180f, true);

	uint normal[3] = { 0, 1, 2 };
	uint takeDmg[1] = { 3 };

	anim->Add(0, normal, 3);
	anim->Add(1, takeDmg, 1);

	anim->Select(0);

	lookRight = true;

	BBox(new Circle(64));


	life = 2500.f;
}

Shoggoth::~Shoggoth() {
	delete tileset;
	delete anim;
	delete timer;
}

void Shoggoth::OnCollision(Object* obj) {
	if (obj->Type() == PROJECTILE) {
		anim->Delay(0.3f);
		anim->Select(1);
	}
}

void Shoggoth::Update() {
	if (MinutesTillDawn::upgrading) {
		return;
	}

	if (timer->Elapsed() > 3.0f) {
		FireLaser();
		timer->Reset();
	}

	if (anim->Frame() == 3) {
		anim->Select(0);
	}

	if (anim != nullptr)
		anim->NextFrame();
}

void Shoggoth::FireLaser() {
	Laser* laser = new Laser(X(), Y());
	MinutesTillDawn::scene->Add(laser, MOVING);
}

void Shoggoth::Draw() {

	anim->Draw(X(), Y(), Layer::MIDDLE);
}