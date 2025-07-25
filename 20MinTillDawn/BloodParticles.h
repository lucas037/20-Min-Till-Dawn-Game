#pragma once

#include "Object.h"    
#include "Types.h"
#include "Particles.h"

#include <random>
using std::random_device;
using std::mt19937;
using Rnd = std::uniform_real_distribution<float>;

// ---------------------------------------------------------------------------------

class BloodParticles : public Object
{
private:
    Particles* starGen;            // sistema de part�culas
    random_device rd;               // gerador de n�mero aleat�rio
    mt19937 mt{ rd() };             // gerador mersenne twister
    Rnd RandAngle{ 0.0f, 359.0f };  // �ngulo aleat�rio
    Rnd RandColor{ 0.0f, 1.0f };    // cor aleat�ria
    float upperTime = 0.0f;         // tempo que ela vai ficar indo para cima
	float lifeCount = 0.0f;          // contador de vida da part�cula

public:
    BloodParticles(float x, float y);                    // construtor
    ~BloodParticles();                   // destrutor

    int  Size();                    // quantidade de part�culas
    void Update();                  // atualiza��o
    void Draw();                    // desenho
};