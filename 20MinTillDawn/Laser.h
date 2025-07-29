#include "Object.h"
#include "TileSet.h"
#include "Animation.h"


class Laser : public Object {
private:
	TileSet* tileset;
	Animation* anim;
	Timer* timer;

	float x, y, sX, sY, rotation; // rotação do laser
	bool firing; // indica se o laser está disparando

public:
	Laser(float Sx, float Sy);
	~Laser();

	void Update();
	void Draw();

	void FollowPlayer();
};

inline void Laser::Draw() {
	anim->Draw(x, y, Layer::MIDDLE, 1.0f, rotation);
}