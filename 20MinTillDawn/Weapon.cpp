#include "Weapon.h"
#include "TileSet.h"
#include "Config.h"

bool flipped = false;

Weapon::Weapon(Character* newCharacter, string newSprite) {
	reloadTimer = new Timer();

	TileSet* tileSet = new TileSet(newSprite, 32, 32, 5, 10);
	anim = new Animation(tileSet, 0.1f, true);

	uint rightGun[1] = { 0 };
	uint leftGun[1] = { 5 };
	uint rightReload[4] = { 1, 2, 3, 4 };
	uint leftReload[4] = { 6, 7, 8, 9 };

	anim->Add(RIGHTGUN, rightGun, 1);
	anim->Add(LEFTGUN, leftGun, 1);
	anim->Add(RIGHTRELOAD, rightReload, 4);
	anim->Add(LEFTRELOAD, leftReload, 4);

	anim->Select(RIGHTGUN);

	character = newCharacter;

	x = character->X();
	y = character->Y();

	MoveTo(x, y);

	direction = new Vector(0, 0);
	reloading = false;
	numShots = Config::numMaxShots;
}

Weapon::~Weapon()
{
	delete anim;
}

void Weapon::Update() {
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

	float deltaX = aimX - centerX;
	float deltaY = aimY - centerY;

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

		if (reloading)
			anim->Frame(frame);

		flipped = true;
	}
	else if ((rotation < 90 || rotation > 270) && flipped)
	{
		int frame = anim->Frame() - 4;

		if (reloading)
			anim->Frame(frame);

		flipped = false;
	}

	if (reloading)
	{
		anim->Select(flipped ? LEFTRELOAD : RIGHTRELOAD);
	}
	else {
		anim->Select(flipped ? LEFTGUN : RIGHTGUN);
	}

	if (reloading)
	{
		anim->NextFrame();

		if (reloadTimer->Elapsed() > Config::ReloadTime)
		{
			numShots = Config::numMaxShots;
			reloadTimer->Reset();
			reloadTimer->Stop();
			reloading = false;
		}
	}
}

void Weapon::Reload() {
	reloading = true;
	reloadTimer->Start();
}

bool Weapon::Reloading() {
	return reloading;
}
