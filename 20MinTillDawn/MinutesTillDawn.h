/**********************************************************************************
// GeoWars (Arquivo de Cabeçalho)
// 
// Criação:     23 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Demonstração da versão final do motor
//
**********************************************************************************/

#ifndef _MINUTESTILLDAWN_H_
#define _MINUTESTILLDAWN_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "Heart.h"
#include "Vector.h"
#include "Controller.h"
#include "HomeScreen.h"

using namespace std;

// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, MISSILE, BLUE, GREEN, MAGENTA, ORANGE, WALLHIT, ENEMY, TENTACLE };

// ------------------------------------------------------------------------------

enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL };

enum ScreensIds { GOHOME, GOLEVEL };

// ------------------------------------------------------------------------------

class MinutesTillDawn : public Game
{
private:
    Background * backg = nullptr;   // pano de fundo
    bool viewBBox = false;          // visualização das bouding boxes

public:
    static Player * player;         // nave controlada pela jogador
	static Character* character;    // personagem do jogador
    static Audio * audio;           // sitema de áudio
    static Scene * scene;           // cena do jogo
    static bool viewHUD;            // visualização do painel
    static Controller * controller;
	static bool xboxOn;             // gamepad xbox conectado
	static bool controllerOn;       // gamepad conectado

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização

    static void NextLevel(int screen)
    {
        game->Finalize();

        switch (screen) {
        case GOLEVEL:
            game = new MinutesTillDawn();
            game->Size(3840, 2160);
            break;
        case GOHOME:
            game = new HomeScreen();
            game->Size(1024, 720);
            break;
        }

        game->Init();
    };
};

// ---------------------------------------------------------------------------------

#endif