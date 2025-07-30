#include "TentacleMonster.h"
#include "MinutesTillDawn.h"
#include "Aleatory.h"
#include "Config.h"

TentacleMonster::TentacleMonster(): Enemy(){
	tileset = new TileSet("Resources/Enemy_Brain.png", 128, 128, 4, 4);
	anim = new Animation(tileset, 0.180f, true);

	uint walk[4] = { 0, 1, 2, 3 };

	anim->Add(0, walk, 4);
	anim->Select(0);

	UpdateSprite(spriteR);
	lookRight = true;

	BBox(new Rect(-24, -24, 24, 24));

	float difficutyFactor = 1.3;

	float timeElapsed = MinutesTillDawn::stageTimer.Elapsed();

	if (timeElapsed < (1.0/4)*(Config::stageTotalTime)) { // 25% do tempo
		life = Aleatory::randrange(24* difficutyFactor, 60 * difficutyFactor);
	}
	else if (timeElapsed < (2.0 / 4) * (Config::stageTotalTime)) { // 50% do tempo
		life = Aleatory::randrange(60 * difficutyFactor, 80 * difficutyFactor);
	}
	else {
		life = Aleatory::randrange(80 * difficutyFactor, 250 * difficutyFactor);

		tileset = new TileSet("Resources/Enemy_Lamprey.png", 128, 128, 5, 5);
		anim = new Animation(tileset, 0.180f, true);
		uint walkv2[5] = { 0, 1, 2, 3, 4 };

		anim->Add(1, walkv2, 4);
		anim->Select(1);

		BBox(new Rect(-48, -48, 48, 48));
	}
}

TentacleMonster::~TentacleMonster() {

}