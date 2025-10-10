/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#ifndef _MINUTESTILLDAWN_PLAYER_H_
#define _MINUTESTILLDAWN_PLAYER_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                        // objetos do jogo
#include "Sprite.h"                        // desenho de sprites
#include "Vector.h"                        // representação de vetores
#include "Particles.h"                    // sistema de partículas
#include "Character.h"                    // personagem do jogador

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    Sprite * sprite;                    // sprite do objeto
    Particles * tail;                   // calda do jogador

public:
    Vector * speed;                     // velocidade e direção
    
    // Struct para as estatísticas da run
    struct RunStats {
        int enemiesKilled = 0;
        int upgradesObtained = 0;
        float survivalTime = 0.0f;
        
        void Reset() {
            enemiesKilled = 0;
            upgradesObtained = 0;
            survivalTime = 0.0f;
        }
    };
    
    RunStats stats;  // Instância do struct de estatísticas

    Player();                           // construtor
    ~Player();                          // destrutor
    
    void Move(Vector && v);             // movimenta jogador
    void Update();                      // atualização
    void Draw();                        // desenho
    
    // Métodos para gerenciar estatísticas
    void ResetStats();                  
    void AddEnemyKilled();             
    void AddUpgradeObtained();         
    void UpdateSurvivalTime(float time); 
}; 
// ---------------------------------------------------------------------------------

#endif