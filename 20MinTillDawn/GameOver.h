#pragma once
#include "Scene.h"
#include "Background.h"
#include "Game.h"
#include <string>


using namespace std;

class GameOver : public Game
{
private:
    Background* backg = nullptr;
    bool viewBBox = false;
    Sprite* border = nullptr;
    int selected = 0; // 0 = Shana, 1 = Diamond

public:
    void Init();
    void Finalize();
    void Update();
    void Draw();
};