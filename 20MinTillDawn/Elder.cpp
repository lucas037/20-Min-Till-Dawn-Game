#include "Elder.h"
#include "MinutesTillDawn.h"
#include "Aleatory.h"
#include "Config.h"

Elder::Elder() : Enemy() {
	spriteR = new Sprite("Resources/MiniBoss_Elder.png");
	spriteL = new Sprite("Resources/MiniBoss_Elder_L.png");

	UpdateSprite(spriteR);
	lookRight = true;

	BBox(new Rect(-24, -24, 24, 24));

	life = 1000.f;
}

Elder::~Elder() {

}