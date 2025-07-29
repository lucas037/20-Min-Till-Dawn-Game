#ifndef WEAPON_H
#define WEAPON_H

#include "Object.h"
#include "Animation.h"
#include "Vector.h"
#include "Character.h"

enum AnimationId {
    RIGHTGUN = 0,
    LEFTGUN,
    RIGHTRELOAD,
    LEFTRELOAD
};

class Weapon : public Object
{
private:
    Animation* anim;
    string projectileSprite;

    Character* character;
    Vector* direction;
    Timer* reloadTimer;

    float x, y, rotation;
    float aimX, aimY;
    bool reloading;

public:
    int numShots;

    Weapon(Character* character, string newSprite);
    ~Weapon();

    void Move(Vector&& v);
    void Move(float x, float y) {
        aimX = x;
        aimY = y;
    }
    void Update();
    void Draw() {
        anim->Draw(x, y, Layer::FRONT, 1.0f, rotation);
    };

    void Reload();
    bool Reloading();
};

#endif // WEAPON_H
