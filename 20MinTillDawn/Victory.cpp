#include "Victory.h"
#include "MinutesTillDawn.h"
#include "Resources.h"
#include "Engine.h"
#include "Game.h"
#include "Font.h"
#include <algorithm>

void Victory::Init()
{
    backg = new Background("Resources/victory.jpg");

    if (!MinutesTillDawn::font16) {
        MinutesTillDawn::font16 = new Font("Resources/font16.png");
        MinutesTillDawn::font16->Spacing("Resources/Font16.dat");
    }

    // calcula posi��o para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;

    MinutesTillDawn::controller = new Controller();
}

void Victory::Finalize()
{
    delete backg;
}

void Victory::Update()
{
    if (window->KeyPress(VK_ESCAPE)) {
        MinutesTillDawn::NextLevel(GOHOME);
    }

    bool xboxOn = MinutesTillDawn::controller->XboxInitialize(0);
    bool confirmButton = false;

    if (xboxOn) {
        MinutesTillDawn::controller->XboxUpdateState();

        confirmButton = MinutesTillDawn::controller->XboxButton(ButtonA);
    }

    if (window->KeyPress(VK_RETURN) || confirmButton) {
        MinutesTillDawn::NextLevel(GOHOME);
    }

}

void Victory::Draw()
{
    if (backg)
    {
        backg->Draw(viewport);
    }

    if (MinutesTillDawn::font16) {
        Color corTexto = { 0.992f, 0.317f, 0.380f, 1.0f };
        Color corStats = { 1.0f, 1.0f, 1.0f, 1.0f };

        float statsY = window->CenterY() ;
        float statsX = window->CenterX() - 200;

        MinutesTillDawn::font16->Draw(statsX, statsY, "ESTATISTICAS DA RUN:", corTexto, 0.0f, 1.0f);

        if (MinutesTillDawn::player) {
            // Inimigos mortos
            string enemiesText = "Inimigos eliminados: " + to_string(MinutesTillDawn::player->stats.enemiesKilled);
            MinutesTillDawn::font16->Draw(statsX, statsY + 40, enemiesText.c_str(), corStats, 0.0f, 1.0f);

            // Upgrades obtidos
            string upgradesText = "Upgrades obtidos: " + to_string(MinutesTillDawn::player->stats.upgradesObtained);
            MinutesTillDawn::font16->Draw(statsX, statsY + 70, upgradesText.c_str(), corStats, 0.0f, 1.0f);

            // Tempo de sobrevivência
            int minutes = (int)(MinutesTillDawn::player->stats.survivalTime / 60.0f);
            int seconds = (int)(MinutesTillDawn::player->stats.survivalTime) % 60;
            string timeText = "Tempo sobrevivido: " + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);
            MinutesTillDawn::font16->Draw(statsX, statsY + 100, timeText.c_str(), corStats, 0.0f, 1.0f);
        }



        MinutesTillDawn::font16->Draw(window->CenterX() - 250 , window->CenterY() + 300, "Pressione ENTER ou ESC para continuar", corStats, 0.0f, 0.8f);
    }
}