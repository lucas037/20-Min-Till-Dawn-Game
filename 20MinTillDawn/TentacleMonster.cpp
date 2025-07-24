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

	UpdateSprite(spriteL);

	BBox(new Rect(-24, -24, 24, 24));

	float timeElapsed = MinutesTillDawn::stageTimer.Elapsed();

	if (timeElapsed < (1.0/4)*(Config::stageTotalTime)) { // 25% do tempo
		life = Aleatory::randrange(24, 60);
	}
	else if (timeElapsed < (2.0 / 4) * (Config::stageTotalTime)) { // 50% do tempo
		life = Aleatory::randrange(60, 80);
	}
	else {
		life = Aleatory::randrange(80, 250);
	}
}

TentacleMonster::~TentacleMonster() {

}