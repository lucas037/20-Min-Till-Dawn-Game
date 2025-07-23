#ifndef AIM_H
#define AIM_H

#include "Object.h"
#include "Vector.h"
#include "Sprite.h"

class Aim : public Object {
private:
	Sprite* sprite;
public:
	bool show = true;
	Aim(float x, float y);
	~Aim();

	void Move(Vector&& v);
	void Update();
	void Draw();
	void ChangeMouseMode(bool newShow) {
		show = newShow;
	}
};
#endif