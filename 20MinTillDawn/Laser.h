#include "Object.h"
#include "TileSet.h"
#include "Animation.h"


class Laser : public Object {
private:
	TileSet* tileset;
	Animation* anim;

	float rotation; // rotação do laser
	bool firing; // indica se o laser está disparando
public:
	Laser();
	~Laser();

	void Update();
	void Draw();
}
