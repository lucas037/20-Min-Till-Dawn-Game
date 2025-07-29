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
	uint takeDmg[4] = { 3, 0, 3, 0 };

	anim->Add(0, normal, 3);
	anim->Add(1, takeDmg, 4);

	anim->Select(0);

	lookRight = true;

	BBox(new Circle(64));

	life = 2500.f;
}

Shoggoth::~Shoggoth() {

}

void Shoggoth::Update() {
	if (MinutesTillDawn::upgrading) {
		return;
	}

	if (timer->Elapsed() > 3.0f) {
		FireLaser();
		timer->Reset();
	}

	if (anim != nullptr)
		anim->NextFrame();
}

void Shoggoth::FireLaser() {
	Laser* laser = new Laser(X(), Y());
	MinutesTillDawn::scene->Add(laser, STATIC);
}

void Shoggoth::Draw() {

	anim->Draw(X(), Y(), Layer::MIDDLE);
}