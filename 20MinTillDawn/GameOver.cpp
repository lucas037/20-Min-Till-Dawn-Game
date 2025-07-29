#include "GameOver.h"
#include "MinutesTillDawn.h"
#include "Resources.h"
#include "Engine.h"
#include "Game.h"

void GameOver::Init()
{
    backg = new Background("Resources/selectscreen.jpg");
    border = new Sprite("Resources/selectborder.png");

    // calcula posição para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;


}

void GameOver::Finalize()
{
    delete backg;
    delete border;
}

void GameOver::Update()
{
    if (window->KeyPress(VK_ESCAPE)) {
        MinutesTillDawn::NextLevel(GOHOME);
    }

    // Seleciona a Diamond
    if ((window->KeyPress(VK_RIGHT) || window->KeyPress('D')) && selected == 0) {
        selected = 1;
    }

    // Seleciona a Shana
    if ((window->KeyPress(VK_LEFT) || window->KeyPress('A')) && selected == 1) {
        selected = 0;
    }

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

    Color corTexto = { 0.992f, 0.317f, 0.380f, 1.0f };
    MinutesTillDawn::font16->Draw(window->CenterX() - 150, window->CenterY() - 250, "GAME OVER", corTexto, 0.0f, 1.0f);

    // Posicoes da borda
    float border_x[2] = { window->CenterX() - 250, window->CenterX() + 275 };
    float border_y = window->CenterY() + 50;

    // Desenha a borda 
    if (border)
        border->Draw(border_x[selected], border_y);


}