#include "Enemy.h"
#include "Sprite.h"
#include "Animation.h"

class Shoggoth : public Enemy {
private:
	Timer* timer;

	TileSet* tileset_laser;
	Animation* anim_laser;

	float laserX, laserY, rotation;
	bool shooting = false;

public:
	Shoggoth();
	~Shoggoth();

	void Update();
	void Draw();

	void Laser();
};