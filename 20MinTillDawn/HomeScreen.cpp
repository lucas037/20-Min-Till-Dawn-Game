#include "HomeScreen.h"
#include "MinutesTillDawn.h"
#include "Resources.h"
#include "Engine.h"
#include "Game.h"
#include "Font.h"

void HomeScreen::Init()
{
    backg = new Background("Resources/homescreen.jpg");

    if (!MinutesTillDawn::font16) {
        MinutesTillDawn::font16 = new Font("Resources/font16.png");
        MinutesTillDawn::font16->Spacing("Resources/Font16.dat");
    }

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
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_RETURN)) {
        MinutesTillDawn::NextLevel(GOSELECTCHAR);
    }
}

void HomeScreen::Draw()
{
    if (backg)
    {
        backg->Draw(viewport);
    }

    Color corTexto = { 0.992f, 0.317f, 0.380f, 1.0f };

    if (MinutesTillDawn::font16) {
        MinutesTillDawn::font16->Draw(window->CenterX() - 175, window->CenterY() + 100, "Aperte ENTER para iniciar", corTexto);
    }
}