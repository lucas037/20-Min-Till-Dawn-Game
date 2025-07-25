/**********************************************************************************
// GeoWars (Arquivo de Cabe�alho)
// 
// Cria��o:     23 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Demonstra��o da vers�o final do motor
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
#include "SelectChar.h"
#include "Enemy.h"
#include "Aim.h"
#include "Weapon.h"
#include "Font.h"

using namespace std;

// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, MISSILE, BLUE, GREEN, MAGENTA, ORANGE, WALLHIT, ENEMY, TENTACLE, REPULSION_AREA, PROJECTILE};

// ------------------------------------------------------------------------------

enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL };

enum ScreensIds { GOHOME, GOLEVEL, GOSELECTCHAR };

// ------------------------------------------------------------------------------

class MinutesTillDawn : public Game  
{  
private:  
    Background * backg = nullptr;   // pano de fundo  
    bool viewBBox = false;          // visualiza��o das bouding boxes  

    Timer* enemiesSpawnTimer = new Timer();  
    Timer* shotTimer = new Timer();  
    bool elderSpawned = false;  

public:  
    static Player * player;         // nave controlada pela jogador  
    static Character* character;    // personagem do jogador  
    static Audio * audio;           // sitema de �udio  
    static Scene * scene;           // cena do jogo  
    static bool viewHUD;            // visualiza��o do painel  
    static Controller * controller;  
    static bool xboxOn;             // gamepad xbox conectado  
    static bool controllerOn;       // gamepad conectado  
    static int newEnemyId;  
    static Timer stageTimer;  
    static std::vector<Enemy*> enemies;  
    bool aimMouseMode = true;  
    static Font* font16;  

    Weapon* weapon;  
    Aim* aim;  

    void Init();                    // inicializa��o  
    void Update();                  // atualiza��o  
    void Draw();                    // desenho  
    void Finalize();                // finaliza��o  

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
        case GOSELECTCHAR:  
            game = new SelectChar();  
            game->Size(1024, 720);  
            break;  
        }  

        game->Init();  
    };  
};

// ---------------------------------------------------------------------------------

#endif