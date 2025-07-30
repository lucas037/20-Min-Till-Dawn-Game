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

    Generator trailConfig;

    trailConfig.imgFile = "Resources/Projectile.png";
    trailConfig.lifetime = 0.2f;
    trailConfig.frequency = 0.005f;
    trailConfig.percentToDim = 0.3f;
    trailConfig.minSpeed = 0.0f;
    trailConfig.maxSpeed = 0.0f;
    trailConfig.angle = rotation; // Angulo
    trailConfig.spread = 0.0f;
    trailConfig.color.r = 1.0f;
    trailConfig.color.g = 1.0f;
    trailConfig.color.b = 1.0f;
    trailConfig.color.a = 1.0f;

    trailEmitter = new Particles(trailConfig);
    
    MoveTo(x, y);

    speed = new Vector(XMConvertToDegrees(angle), speedMag);

    BBox(new Circle(12.0f));
    type = PROJECTILE;
}

Projectile::~Projectile() {
    delete anim;
	delete speed;
    delete trailEmitter;
}

void Projectile::OnCollision(Object* obj) {
    if (obj->Type() == ENEMY) {
        anim->Frame(0);
        anim->Select(HIT);
		hitting = true;
    }
}

void Projectile::Update() {
    if (MinutesTillDawn::upgrading)
        return;

    Translate(speed->XComponent() * gameTime, speed->YComponent() * gameTime);
    trailEmitter->Generate(X(), Y());

    trailEmitter->Update(gameTime);

    // Scale down each particle based on its percentage of lifespan passed
    for (uint i = 0; i < trailEmitter->Size(); ++i) {
        Particle* particle = trailEmitter->Get(i); // Assumes GetParticle returns a reference to a particle
		float percent = particle->timestamp / 0.08f; // Percentage of lifetime passed
        float scale = 1.0f - percent; // Shrink from 1.0 to 0.0
        if (scale < 0.0f) scale = 0.0f;
        
    }
    
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
    trailEmitter->Draw(Layer::UPPER + 0.01);
    anim->Draw(x, y, Layer::UPPER, 1.0f, rotation);
}
