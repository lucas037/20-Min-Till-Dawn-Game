/**********************************************************************************
// GeoWars (Código Fonte)
// 
// Criação:     23 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Demonstração da versão final do motor
//
**********************************************************************************/

#include "Resources.h"
#include "GeoWars.h"
#include "Engine.h"    
#include "TentacleMonster.h"    
#include "Character.h"
#include "Heart.h"
#include "Audio.h"
#include "Weapon.h"

// ------------------------------------------------------------------------------

Player * GeoWars::player  = nullptr;
Audio  * GeoWars::audio   = nullptr;
Scene  * GeoWars::scene   = nullptr;
bool     GeoWars::viewHUD = true;

// ------------------------------------------------------------------------------

void GeoWars::Init() 
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(THEME, "OldResources/Theme.wav");
    audio->Add(FIRE, "OldResources/Fire.wav");
    audio->Add(HITWALL, "OldResources/Hitwall.wav");
    audio->Add(EXPLODE, "OldResources/Explode.wav");
    audio->Add(START, "OldResources/Start.wav");

    // ajusta volumes
    audio->Volume(FIRE, 0.2f);
    audio->Volume(START, 0.8f);
    audio->Volume(THEME, 0.6f);

    // carrega/incializa objetos
    backg   = new Background("OldResources/Space.jpg");
    player  = new Player();
    scene   = new Scene();

	Character* charac = new Character();
	scene->Add(charac, MOVING);
    
    Weapon* weapon = new Weapon(charac, "Resources/Revolver.png", "");
    scene->Add(weapon, MOVING);

    TentacleMonster* enemy;

    for (int i = 0; i < 3; i++) {
        enemy = new TentacleMonster();
        scene->Add(enemy, MOVING);
    }

    // ----------------------
    // inicializa a viewport
    // ----------------------

    // calcula posição para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;

    // inicializa viewport para o centro do mundo
    viewport.left = 0.0f + difx;
    viewport.right = viewport.left + window->Width();
    viewport.top = 0.0f + dify;
    viewport.bottom = viewport.top + window->Height();
}

// ------------------------------------------------------------------------------

void GeoWars::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza cena e calcula colisões
    scene->Update();
    scene->CollisionDetection();

    // ativa ou desativa a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // ativa ou desativa o heads up display
    if (window->KeyPress('H'))
        viewHUD = !viewHUD;

    // --------------------
    // atualiza a viewport
    // --------------------

    viewport.left   = player->X() - window->CenterX();
    viewport.right  = player->X() + window->CenterX();
    viewport.top    = player->Y() - window->CenterY();
    viewport.bottom = player->Y() + window->CenterY();
            
    if (viewport.left < 0)
    {
        viewport.left  = 0;
        viewport.right = window->Width();
    }
    else if (viewport.right > game->Width())
    {  
        viewport.left  = game->Width() - window->Width();
        viewport.right = game->Width();
    }
                  
    if (viewport.top < 0)
    {
        viewport.top  = 0;
        viewport.bottom = window->Height();
    }
    else if (viewport.bottom > game->Height())
    {
        viewport.top = game->Height() - window->Height();
        viewport.bottom = game->Height();
    }
} 

// ------------------------------------------------------------------------------

void GeoWars::Draw()
{
    // desenha pano de fundo
    backg->Draw(viewport);

    // desenha a cena
    scene->Draw();

    // desenha bounding box
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void GeoWars::Finalize()
{
    delete audio;
    delete scene;
    delete backg;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor do jogo
    Engine * engine = new Engine();

    // configura motor
    //engine->window->Mode(WINDOWED);
    engine->window->Size(1024, 720);
    engine->window->Mode(BORDERLESS);
    engine->window->Color(0, 0, 0);
    engine->window->Title("GeoWars");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);
    //engine->graphics->VSync(true);

    // cria o jogo
    Game * game = new GeoWars();

    // configura o jogo
    game->Size(3840, 2160);
    
    // inicia execução
    engine->Start(game);

    // destrói motor e encerra jogo
    delete engine;
    return 0;
}

// ----------------------------------------------------------------------------