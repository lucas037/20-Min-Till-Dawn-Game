#pragma once
#include "Scene.h"
#include "Background.h"
#include "Game.h"
#include <string>


using namespace std;

class SelectChar : public Game
{
private:
    Background* backg = nullptr;
    bool viewBBox = false;

public:
    void Init();
    void Finalize();
    void Update();
    void Draw();
};