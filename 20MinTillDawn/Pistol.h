#include "Weapon.h"

class Pistol : public Weapon {
public:
	Pistol(Character* character) : Weapon(character, "Resources/Pistol.png", "Resources/ProjectileFX.png") {};

	//void Reloading() override;
};


