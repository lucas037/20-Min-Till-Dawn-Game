#include "Object.h"
#include "TileSet.h"
#include "Animation.h"


class Laser : public Object {
private:
	TileSet* tileset;
	Animation* anim;

	float rotation; // rota��o do laser
	bool firing; // indica se o laser est� disparando
public:
	Laser();
	~Laser();

	void Update();
	void Draw();
}
