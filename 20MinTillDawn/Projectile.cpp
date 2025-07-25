#include "Projectile.h"
#include "MinutesTillDawn.h"

Projectile::Projectile(float x, float y, float speedMag, float angle) {
	TileSet* tileSet = new TileSet("Resources/ProjectileFX.png", 32, 32, 2, 4);
	anim = new Animation(tileSet, 0.01f, false);

    uint firing[1] = { 0 };
	uint bullet[1] = { 2 };
	uint hit[1]    = { 3 };

	anim->Add(FIRING, firing, 2);
	anim->Add(BULLET, bullet, 2);
	anim->Add(HIT, hit, 60);

	anim->Select(FIRING);
	this->firing = true;
    this->hitting = false;
    
	rotation = XMConvertToDegrees(angle);
    MoveTo(x, y);

    speed = new Vector(XMConvertToDegrees(angle), speedMag);

    BBox(new Circle(12.0f));
    type = PROJECTILE;
}

Projectile::~Projectile() {
    delete anim;
	delete speed;
}

void Projectile::OnCollision(Object* obj) {
    if (obj->Type() == ENEMY) {
        anim->Frame(0);
        anim->Select(HIT);
		hitting = true;
    }
}

void Projectile::Update() {
    Translate(speed->XComponent() * gameTime, speed->YComponent() * gameTime);
    
    if (anim->Inactive() && firing) {
        anim->Frame(0);
		anim->Select(BULLET);
		firing = false;
    }
    else if (firing) {
        anim->NextFrame();
    }

    if (X() < game->viewport.left || X() > game->viewport.right || Y() < game->viewport.top || Y() > game->viewport.bottom) {
        MinutesTillDawn::scene->Delete(this, MOVING);
    }

    if (hitting)
        MinutesTillDawn::scene->Delete(this, MOVING);
}

void Projectile::Draw() {
    anim->Draw(x, y, Layer::UPPER, 1.0f, rotation);
}
