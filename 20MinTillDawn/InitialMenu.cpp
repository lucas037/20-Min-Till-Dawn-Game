#include "InitialMenu.h"
#include "Engine.h"

void InitialMenu::Init() {
	background = new Sprite("Resources/initial.webp");
}

void InitialMenu::Finalize() {
	delete background;
}

void InitialMenu::Update()
{
    // sai do jogo com a tecla ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // passa ao primeiro nível com ENTER
    //if (window->KeyPress(VK_SPACE))
        //Engine::Next<Level1>();
}