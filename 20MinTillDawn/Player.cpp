/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#include "Player.h" 
#include "MinutesTillDawn.h"

// -------------------------------------------------------------------------------

Player::Player()
{
    // configuração do objeto
    sprite = new Sprite("OldResources/Player.png");
    speed  = new Vector(90.0f, 0.0f);
    BBox(new Circle(18.0f));
    MoveTo(game->CenterX(), game->CenterY());
    type = PLAYER;
    
    // Inicializa estatísticas
    ResetStats();
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete sprite;
    delete speed;
    delete tail;
}

// -------------------------------------------------------------------------------

void Player::Move(Vector && v)
{
}

// -------------------------------------------------------------------------------

void Player::Update()
{
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    sprite->Draw(x, y, Layer::MIDDLE, 1.0f, -speed->Angle() + 90.0f);
    if (tail) tail->Draw(Layer::LOWER, 1.0f);
}

// ---------------------------------------------------------------------------------
// MÉTODOS PARA ESTATÍSTICAS
// ---------------------------------------------------------------------------------

void Player::ResetStats()
{
    stats.Reset();
}

void Player::AddEnemyKilled()
{
    stats.enemiesKilled++;
}

void Player::AddUpgradeObtained()
{
    stats.upgradesObtained++;
}

void Player::UpdateSurvivalTime(float time)
{
    stats.survivalTime = time;
}

// -------------------------------------------------------------------------------
