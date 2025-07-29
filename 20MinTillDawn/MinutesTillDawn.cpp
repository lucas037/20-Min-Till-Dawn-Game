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
#include "Elder.h"  
#include "TentacleMonster.h"    
#include "Character.h"
#include "CharShana.h"  
#include "CharDiamond.h"
#include "Heart.h"
#include "Audio.h"
#include "Controller.h"
#include "Projectile.h"
#include "Config.h"
#include "Aleatory.h"
#include "Upgrade.h"
#include "Experience.h"

// ------------------------------------------------------------------------------

uint MinutesTillDawn::selectedChar;
Player * MinutesTillDawn::player  = nullptr;
Character* MinutesTillDawn::character = nullptr;
Audio  * MinutesTillDawn::audio   = nullptr;
Scene  * MinutesTillDawn::scene   = nullptr;
Controller* MinutesTillDawn::controller = nullptr;
bool     MinutesTillDawn::xboxOn = false;
bool     MinutesTillDawn::controllerOn = false;
bool     MinutesTillDawn::viewHUD = true;
bool     MinutesTillDawn::upgrading = false;
bool     MinutesTillDawn::startUpgrade = false;
Timer MinutesTillDawn::stageTimer;
std::vector<Enemy*> MinutesTillDawn::enemies;
int MinutesTillDawn::newEnemyId = 0;
bool     MinutesTillDawn::upgradeFinishing = false;

Font* MinutesTillDawn::font16 = nullptr;
UpgradeIcon* MinutesTillDawn::upIcons[5] = { nullptr };
int MinutesTillDawn::upgradeClick = 0;
std::vector<int> MinutesTillDawn::upgradesIndexes;

// ------------------------------------------------------------------------------

void MinutesTillDawn::Init()
{
	controller = new Controller();

    xboxOn = controller->XboxInitialize(0);

    if (!xboxOn)
        controllerOn = controller->Initialize();

    // cria sistema de �udio
    audio = new Audio();
    audio->Add(DAMAGE, "Resources/DanoRecebido.wav");
    audio->Add(SHOOT, "Resources/Tiro.wav");
    audio->Add(MUSIC_1, "Resources/MusicaDeBatalha.wav");
	audio->Add(WALK, "Resources/Passos.wav");
    audio->Add(LOW_HP, "Resources/Poucavida.wav");

    // ajusta volumes
    audio->Volume(DAMAGE, 1.0f);
	audio->Volume(MUSIC_1, 0.4f);
    audio->Volume(WALK, 0.3f);
    audio->Volume(LOW_HP, 0.08f);

	// fonte de texto
    font16 = new Font("Resources/font16.png");
    font16->Spacing("Resources/Font16.dat");

    // carrega/incializa objetos
    backg   = new Background("OldResources/Space.jpg");
	ammo = new Sprite("Resources/bullet2.png");
    player  = new Player();
    scene   = new Scene();

	if (selectedChar == SHANA) {
		character = new CharShana();
	}
	else if (selectedChar == DIAMOND) {
        character = new CharDiamond();
	}

	scene->Add(character, MOVING);
    
    weapon = new Weapon(character, "Resources/Revolver.png");
    scene->Add(weapon, MOVING);

    player->ResetStats();

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

    stageTimer.Reset();

    aim = new Aim(game->CenterX(), game->CenterY());
    scene->Add(aim, MOVING);

    enemiesSpawnTimer->Reset();
    shotTimer->Reset();
    upgradeTimer->Reset();
    weapon->numShots = Config::numMaxShots;
    elderSpawned = false;
    enemies.clear();

    recoverHpTimer->Reset();

    audio->Play(MUSIC_1, true);

    upgrading = false;
    upgradeFinishing = false;

    Config::minTimeToRecoverHp = Config::stageTotalTime + 1;
    Config::dodgeChance = 0.0f;
    Config::shotDamage = 40.0;
}

// ------------------------------------------------------------------------------

void MinutesTillDawn::Update()
{
    // sai com o pressionamento da tecla ESC

    if (character->lifePoints <= 0) {
        NextLevel(GOGAMEOVER);
        return;
    }

    if (stageTimer.Elapsed() > Config::stageTotalTime) {
        player->UpdateSurvivalTime(stageTimer.Elapsed());
        NextLevel(GOVICTORY);
        return;
    }

    bool scape = false;

    xboxOn = controller->XboxInitialize(0);

    if (!xboxOn) {
        controllerOn = controller->Initialize();
    }
    else {
        controller->XboxUpdateState(0);

        scape = controller->XboxButton(ButtonBack);
    }

    if (window->KeyPress(VK_ESCAPE) || scape) {
        NextLevel(GOHOME);
        return;
    }

    // atualiza cena e calcula colis�es
    scene->Update();
    scene->CollisionDetection();

    if (upgradeFinishing) {
        int indexUp = upgradesIndexes.at(upgradeClick);
        UseUpgrade(indexUp);

        upgradeFinishing = false;
        upgrading = false;
        upgradeTimer->Reset();

        for (int i = 0; i < 5; i++) {
            scene->Remove(upIcons[i], STATIC);
            upIcons[i] = nullptr;
        }

        scene->Remove(upDesc, STATIC);

    }
    else if (upgrading) {
        if (xboxOn) {
            float x = MinutesTillDawn::controller->XboxAnalog(ThumbLX);
            float y = MinutesTillDawn::controller->XboxAnalog(ThumbLY);

            aim->Translate((x / 100) * gameTime, (-y / 100) * gameTime);
        }
        else {
            aim->MoveTo(game->viewport.left + window->MouseX(), game->viewport.top + window->MouseY());
        }

        Color corTexto = { 0.992f, 0.317f, 0.380f, 1.0f };
        font16->Draw(window->CenterX() - 100, window->CenterY() - 250, "Escolha um Upgrade", corTexto, 0.0f, 1.0f);

        return;
    }

    // ativa ou desativa a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    if (window->KeyPress('N')) {
        player->UpdateSurvivalTime(stageTimer.Elapsed());
        NextLevel(GOVICTORY);
        return;
    }
        

    // ativa ou desativa o heads up display
    if (window->KeyPress('H'))
        viewHUD = !viewHUD;

    if (window->KeyPress(VK_SPACE) || ((xboxOn || controllerOn) && aimMouseMode)) {
        aimMouseMode = !aimMouseMode;
    }

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

    if (aimMouseMode) {
        float centerX = window->CenterX();

        aim->MoveTo(game->viewport.left + window->MouseX(), game->viewport.top + window->MouseY());
        weapon->Move(game->viewport.left + window->MouseX(), game->viewport.top + window->MouseY());
    }
    else if (enemies.size() <= 0) {
        aim->MoveTo(0.0, 0.0);
    }
    else {
        int indexClosest = 0;
        Enemy* enemyTest = enemies.at(0);
        float distanceClosest = -1.0;
        
        for (int i = 0; i < enemies.size(); i++) {
            Enemy* enemyTest = enemies.at(i);

            float distanceX = enemyTest->X() - player->X();
            float distanceY = enemyTest->Y() - player->Y();

            float newDistance = distanceX * distanceX + distanceY * distanceY; // a raiz acaba sendo desnecessaria

            if (distanceClosest < 0 || newDistance < distanceClosest) {
                distanceClosest = newDistance;
                indexClosest = i;
            }

        }

        enemyTest = enemies.at(indexClosest);
        aim->MoveTo(enemyTest->X(), enemyTest->Y());
        weapon->Move(enemyTest->X(), enemyTest->Y());
    }

    bool shootPressed = false;

    if (xboxOn) {
        if (controller->XboxTrigger(RightTrigger)) {
            shootPressed = true;
        }
    }
    else if (controllerOn) {
        if (controller->ButtonPress(VK_LBUTTON)) {
            shootPressed = true;
        }
    }
    else if (window->KeyDown(VK_LBUTTON)) {
        shootPressed = true;
    }

    // ATIRA
    if (shootPressed && shotTimer->Elapsed() > Config::shotCountdown && weapon->numShots > 0 && !weapon->Reloading()) {
        shotTimer->Reset();

        float dx = aim->X() - weapon->X();
        float dy = aim->Y() - weapon->Y();
        float angle = atan2(dy, dx);

        Projectile* proj = new Projectile(weapon->X() + 16 * cos(angle), weapon->Y() + 16 * sin(angle), 400.0, angle);
        scene->Add(proj, MOVING);

        audio->Play(SHOOT);

        weapon->numShots--;

        character->shoot(true);
    }
    else if (!weapon->Reloading() && (weapon->numShots == 0 && shootPressed)) {
        weapon->Reload();
    }

    if (startUpgrade) {
        StartUpgrade();
    }

    // ENEMIES
    Enemy* enemy;

    if (enemiesSpawnTimer->Elapsed() > 3 && enemies.size() < Config::numMaxEnemies) {
        enemiesSpawnTimer->Reset();

        for (int i = 0; i < 3; i++) {
            enemy = new TentacleMonster();
            enemies.push_back(enemy);
            scene->Add(enemy, MOVING);
        }
    }

    // Elder spawna uma vez com 25% do jogo completo
    if (MinutesTillDawn::stageTimer.Elapsed() > (Config::stageTotalTime * 0.25) && !elderSpawned) {
        Elder* elder = new Elder();
        enemies.push_back(elder);
        scene->Add(elder, MOVING);

        elderSpawned = true;
    }

    // UPGRADES
    if (recoverHpTimer->Elapsed() > Config::minTimeToRecoverHp) {
        character->AddHeart();
        recoverHpTimer->Reset();
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


    // munição
    if (viewHUD && font16 && weapon && ammo) {
        Color corTexto = { 1.0f, 1.0f, 1.0f, 1.0f };

        float screenX = 50.0f;
        float screenY = 100.0f;

        float worldX = viewport.left + screenX;
        float worldY = viewport.top + screenY;

        float spriteScale = 0.6f;
        ammo->Draw(worldX, worldY, Layer::FRONT, spriteScale);

        string bulletsText = to_string(weapon->numShots) + "/" + to_string(Config::numMaxShots);
        font16->Draw(screenX + 50, screenY + 5, bulletsText.c_str(), corTexto, 0.0f, 1.0f);

        if (weapon->Reloading()) {
            Color corRecarga = { 1.0f, 0.5f, 0.0f, 1.0f };
            font16->Draw(screenX + 18.0f, screenY + 30.0f, "Recarregando...", corRecarga, 0.0f, 0.8f);
        }
    }
    
    // timer
    if (viewHUD && font16) {
        Color corTimer = { 0.992f, 0.317f, 0.380f, 1.0f };

        float timerX = window->Width() - 150.0f; 
        float timerY = 30.0f;                   

        float elapsedTime = stageTimer.Elapsed();
        int minutes = (int)(elapsedTime / 60.0f);
        int seconds = (int)(elapsedTime) % 60;

        string timeText = (minutes < 10 ? "0" : "") + to_string(minutes) + ":" +
            (seconds < 10 ? "0" : "") + to_string(seconds);

        font16->Draw(timerX, timerY, timeText.c_str(), corTimer, 0.0f, 1.2f);
    }
}

// ------------------------------------------------------------------------------

void MinutesTillDawn::Finalize()
{
    delete audio;
    delete scene;
    delete backg;
    delete ammo;    

    delete enemiesSpawnTimer;
    delete shotTimer;
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

void MinutesTillDawn::StartUpgrade() {
    aim->MoveTo(game->viewport.left + 512, game->viewport.top + 360);

    upgrading = true;
    upgradeClick = 0;

    float posX = game->viewport.left + window->Width() / 2 - 125.0f * 2;
    float posY = game->viewport.top + window->Height() / 2 - 150.0f;

    upgradesIndexes = Aleatory::GenerateNumbersList(5, 0, Upgrade::GetUpgradeCount(), false);

    for (int i = 0; i < 5; i++) {
        int iconId = Upgrade::GetUpgrade(upgradesIndexes.at(i)).iconId;

        upIcons[i] = new UpgradeIcon(posX + i * 125.0f, posY, iconId);
        scene->Add(upIcons[i], STATIC);
    }

    upDesc = new UpgradeDescription("Title", "Description");
    scene->Add(upDesc, STATIC);

	this->startUpgrade = false;
}

void MinutesTillDawn::UseUpgrade(int index) {
    int upType = Upgrade::GetUpgrade(index).type;

    if (upType == SK_HEALTH) {
        character->AddMaxHeart();
    }
    else if (upType == SK_GIANT) {
        character->AddMaxHeart();
        character->AddMaxHeart();
        character->AddMaxHeart();

        if (character->Scale() < 2.00)
            character->Scale(1.25f);
    }
    else if (upType == SK_REGENERATION) {
        recoverHpTimer->Reset();
        Config::minTimeToRecoverHp = 60.0f;
    }
    else if (upType == SK_EVASIVE) {
        Config::dodgeChance += 0.25;
    }
    else if (upType == SK_TINY && character->Scale() > 0.25) {
        Config::dodgeChance += 0.05;
        character->Scale(0.75f);
    }
    else if (upType == SK_FASTUPGRADE && Config::timeToUpgrade > 10.0f) {
        Config::timeToUpgrade -= 10.0f;
    }
    else if (upType == SK_BULLETDAMAGE) {
        Config::shotDamage *= 1.4;
    }

    player->AddUpgradeObtained();
}