#include "Weapon.h"
#include "TileSet.h"

bool flipped = false;

Weapon::Weapon(Character* newCharacter, string newSprite, string newProjectileSprite) {
	TileSet* tileSet = new TileSet(newSprite, 32, 32, 5, 10);
	anim = new Animation(tileSet, 0.1f, true);

	uint rightReload[5] = { 0, 1, 2, 3, 4 };
	uint leftReload[5] = { 5, 6, 7, 8, 9 };

	anim->Add(RIGHTRELOAD, rightReload, 5);
	anim->Add(LEFTRELOAD, leftReload, 5);

	anim->Select(RIGHTRELOAD);

	projectileSprite = newProjectileSprite;

	character = newCharacter;

	x = character->X();
	y = character->Y();

	MoveTo(x, y);

	direction = new Vector(0, 0);
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

	// centro do movimento
	// coordenadas globais
	float centerX = character->X();
	float centerY = character->Y();

	// raio do movimento
	float radius = 15.0f;

	// Coordenadas locais
	float mouseX = window->MouseX() + game->viewport.left;
	float mouseY = window->MouseY() + game->viewport.top;

	float deltaX = mouseX - centerX;
	float deltaY = mouseY - centerY;

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
