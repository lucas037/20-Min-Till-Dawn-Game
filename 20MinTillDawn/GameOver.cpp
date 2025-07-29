#include "GameOver.h"
#include "MinutesTillDawn.h"
#include "Resources.h"
#include "Engine.h"
#include "Game.h"

void GameOver::Init()
{
    backg = new Background("Resources/gameover.jpg");

    // calcula posição para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;


}

void GameOver::Finalize()
{
    delete backg;
}

void GameOver::Update()
{

    if (window->KeyPress(VK_RETURN)) {
        MinutesTillDawn::NextLevel(GOHOME);
    }
}

void GameOver::Draw()
{
    if (backg)
    {
        backg->Draw(viewport);
    }
}