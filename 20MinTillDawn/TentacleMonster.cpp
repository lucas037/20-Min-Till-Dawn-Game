#include "TentacleMonster.h"
#include "MinutesTillDawn.h"

TentacleMonster::TentacleMonster(): Enemy(){
	spriteL = new Sprite("Resources/Tentacle-Monster-L.png");
	spriteR = new Sprite("Resources/Tentacle-Monster-R.png");

	UpdateSprite(spriteL);

	BBox(new Rect(-24, -24, 24, 24));
}

TentacleMonster::~TentacleMonster() {

}