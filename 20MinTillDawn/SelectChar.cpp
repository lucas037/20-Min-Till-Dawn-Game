#include "SelectChar.h"
#include "MinutesTillDawn.h"
#include "Resources.h"
#include "Engine.h"
#include "Game.h"

void SelectChar::Init()
{
    backg = new Background("Resources/SelectCharScreen.png");

    // calcula posição para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;


}

void SelectChar::Finalize()
{
    delete backg;
}

void SelectChar::Update()
{
    if (window->KeyPress(VK_ESCAPE)) {
        MinutesTillDawn::NextLevel(GOHOME);
    }

    if (window->KeyPress(VK_RETURN)) {
        MinutesTillDawn::NextLevel(GOLEVEL);
    }
}

void SelectChar::Draw()
{
    if (backg)
    {
        backg->Draw(viewport);
    }
}