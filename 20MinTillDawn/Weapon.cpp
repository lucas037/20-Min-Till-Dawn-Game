#include "Weapon.h"
#include "TileSet.h"

bool flipped = false;
float centerX;
float centerY;

Weapon::Weapon(Character* character, string newSprite, string newProjectileSprite) {
	TileSet* tileSet = new TileSet(newSprite, 32, 32, 5, 10);
	anim = new Animation(tileSet, 0.1f, true);

	uint rightReload[5] = { 0, 1, 2, 3, 4 };
	uint leftReload[5] = { 5, 6, 7, 8, 9 };

	anim->Add(RIGHTRELOAD, rightReload, 5);
	anim->Add(LEFTRELOAD, leftReload, 5);

	anim->Select(RIGHTRELOAD);

	projectileSprite = newProjectileSprite;

	x = character->X();
	y = character->Y();

	centerX = character->X();
	centerY = character->Y();

	MoveTo(x, y);
}

Weapon::~Weapon()
{
	delete anim;
}

void Weapon::Update() {
	if (window->KeyDown(VK_LBUTTON))
	{ 
	}

	//-------------------------------
	//        Posicionamento
	//-------------------------------

	// raio do movimento
	float radius = 15.0f;

	// Coordenadas locais
	float mouseX = window->MouseX() + game->viewport.left;
	float mouseY = window->MouseY() + game->viewport.top;

	float deltaX = aimX - centerX + game->viewport.left;
	float deltaY = aimY - centerY + game->viewport.top;

	float angle = atan2(deltaY, deltaX);

	x = centerX + radius * cos(angle);
	y = centerY + radius * sin(angle);

	// coordenadas globais
	MoveTo(x, y);

	rotation = XMConvertToDegrees(angle);

	if (rotation > 360)
		rotation -= 360;
	else if (rotation < 0)
		rotation += 360;

	if (rotation > 90 && rotation < 270 && !flipped)
	{
        int frame = anim->Frame();
        anim->Select(LEFTRELOAD);
        anim->Frame(frame);

		flipped = true;
	}
	else if ((rotation < 90 || rotation > 270) && flipped)
	{
		int frame = anim->Frame() - 5;
		anim->Select(RIGHTRELOAD);
		anim->Frame(frame);

		flipped = false;
	}
}
