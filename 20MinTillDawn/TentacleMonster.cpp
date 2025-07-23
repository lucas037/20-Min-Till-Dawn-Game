#include "TentacleMonster.h"
#include "MinutesTillDawn.h"
#include "Aleatory.h"

TentacleMonster::TentacleMonster(): Enemy(){
	spriteL = new Sprite("Resources/Tentacle-Monster-L.png");
	spriteR = new Sprite("Resources/Tentacle-Monster-R.png");

	tileset = new TileSet("Resources/Enemy_Brain.png", 128, 128, 4, 4);
	anim = new Animation(tileset, 0.180f, true);

	uint walk[4] = { 0, 1, 2, 3 };

	anim->Add(0, walk, 4);
	anim->Select(0);

	UpdateSprite(spriteL);

	BBox(new Rect(-24, -24, 24, 24));

	float timeElapsed = MinutesTillDawn::stageTimer.Elapsed();

	if (timeElapsed < (3 * 60.0)) { // 3 min
		life = Aleatory::randrange(24, 60);
	}
	else if (timeElapsed < (5 * 60.0)) { // 5min
		life = Aleatory::randrange(60, 80);
	}
	else { // 10 min
		life = Aleatory::randrange(80, 250);
	}
}

TentacleMonster::~TentacleMonster() {

}