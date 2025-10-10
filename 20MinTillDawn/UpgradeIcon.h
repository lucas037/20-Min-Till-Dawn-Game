#ifndef UPGRADEICON_H
#define UPGRADEICON_H

#include "Object.h"
#include "Vector.h"
#include "Sprite.h"
#include "Timer.h"
#include "Animation.h"

class UpgradeIcon : public Object {
private:
    Sprite* sprite;
    Timer* activeTimer = new Timer();
    bool reductSize;

    TileSet* tileset;
    Animation* anim;

public:
    UpgradeIcon(float x, float y, int pos);
    ~UpgradeIcon();

    void OnCollision(Object* obj);
    void Update();
    void Draw();
};

#endif
