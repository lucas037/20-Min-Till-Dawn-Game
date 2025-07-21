#include "HomeScreen.h"
#include "MinutesTillDawn.h"
#include "Resources.h"
#include "Engine.h"
#include "Game.h"

void HomeScreen::Init()
{
    backg = new Background("Resources/HomeScreen.png");

    // calcula posição para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;


}

void HomeScreen::Finalize()
{
    delete backg;
}

void HomeScreen::Update()
{
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (window->KeyDown(VK_RETURN)) {
        MinutesTillDawn::NextLevel(GOLEVEL);
    }
}

void HomeScreen::Draw()
{
    if (backg)
    {
        backg->Draw(viewport);
    }
}