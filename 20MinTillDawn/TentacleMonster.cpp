#include "TentacleMonster.h"

TentacleMonster::TentacleMonster(): Enemy(){
	spriteL = new Sprite("Resources/Tentacle-Monster-L.png");
	spriteR = new Sprite("Resources/Tentacle-Monster-R.png");

	UpdateSprite(spriteL);
}

TentacleMonster::~TentacleMonster() {

}