#include "TentacleMonster.h"

TentacleMonster::TentacleMonster(): Enemy(){
	spriteL = new Sprite("Resources/Tentacle-Monster-L.png");
	spriteR = new Sprite("Resources/Tentacle-Monster-R.png");

	UpdateSprite(spriteL);

	BBox(new Rect(-32, -32, 32, 32));
}

TentacleMonster::~TentacleMonster() {

}