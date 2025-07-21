/**********************************************************************************
// GeoWars (C�digo Fonte)
// 
// Cria��o:     23 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Demonstra��o da vers�o final do motor
//
**********************************************************************************/

#include "Resources.h"
#include "MinutesTillDawn.h"
#include "Engine.h"    
#include "TentacleMonster.h"    
#include "Character.h"
#include "Heart.h"
#include "Audio.h"
#include "Weapon.h"
#include "Controller.h"

// ------------------------------------------------------------------------------

Player * MinutesTillDawn::player  = nullptr;
Audio  * MinutesTillDawn::audio   = nullptr;
Scene  * MinutesTillDawn::scene   = nullptr;
Controller* MinutesTillDawn::controller = nullptr;
bool     MinutesTillDawn::xboxOn = false;
bool     MinutesTillDawn::controllerOn = false;
bool     MinutesTillDawn::viewHUD = true;

// ------------------------------------------------------------------------------

void MinutesTillDawn::Init()
{
	controller = new Controller();

    xboxOn = controller->XboxInitialize(0);

    if (!xboxOn)
        controllerOn = controller->Initialize();

    // cria sistema de �udio
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

    // calcula posi��o para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;

    // inicializa viewport para o centro do mundo
    viewport.left = 0.0f + difx;
    viewport.right = viewport.left + window->Width();
    viewport.top = 0.0f + dify;
    viewport.bottom = viewport.top + window->Height();
}

// ------------------------------------------------------------------------------

void MinutesTillDawn::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyPress(VK_ESCAPE)) {
        NextLevel(GOHOME);
        return;
    }

    xboxOn = controller->XboxInitialize(0);

    if (!xboxOn)
        controllerOn = controller->Initialize();

    // atualiza cena e calcula colis�es
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

void MinutesTillDawn::Draw()
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

void MinutesTillDawn::Finalize()
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
    engine->window->Title("MinutesTillDawn");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);
    //engine->graphics->VSync(true);

    // cria o jogo
    Game * game = new HomeScreen();

    // configura o jogo
    game->Size(1024, 720);
    
    // inicia execu��o
    engine->Start(game);

    // destr�i motor e encerra jogo
    delete engine;
    return 0;
}

// ----------------------------------------------------------------------------