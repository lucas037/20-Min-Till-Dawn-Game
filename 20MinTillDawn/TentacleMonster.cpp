#include "TentacleMonster.h"
#include "MinutesTillDawn.h"
#include "Aleatory.h"

TentacleMonster::TentacleMonster(): Enemy(){
	spriteL = new Sprite("Resources/Tentacle-Monster-L.png");
	spriteR = new Sprite("Resources/Tentacle-Monster-R.png");

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