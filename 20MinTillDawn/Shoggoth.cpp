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

	BBox(new Circle(96));

	life = 2500.f;
	shooting = true;
}

Shoggoth::~Shoggoth() {

}

void Shoggoth::Update() {
	//if (timer->Elapsed() > 20.0) {
	Laser();
		//shooting = true;
	//}

	if (anim != nullptr)
		anim->NextFrame();
}

void Shoggoth::Laser() {



	timer->Reset();
}

void Shoggoth::Draw() {

	anim->Draw(X(), Y(), Layer::MIDDLE);

	if (shooting) {
		anim_laser->Draw(laserX , laserY, Layer::MIDDLE, 1.0f, rotation);
	}
}