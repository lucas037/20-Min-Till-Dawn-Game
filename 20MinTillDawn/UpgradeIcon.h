#ifndef UPGRADEICON_H
#define UPGRADEICON_H

#include "Object.h"
#include "Vector.h"
#include "Sprite.h"
#include "Timer.h"

class UpgradeIcon : public Object {
private:
    Sprite* sprite;
    Timer* activeTimer = new Timer();
    bool reductSize;

public:
    UpgradeIcon(Sprite* sprite, float x, float y);
    ~UpgradeIcon();

    void OnCollision(Object* obj);
    void Update();
    void Draw();
};

#endif
