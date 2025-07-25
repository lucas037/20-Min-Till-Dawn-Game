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
    Particles* starGen;            // sistema de partículas
    random_device rd;               // gerador de número aleatório
    mt19937 mt{ rd() };             // gerador mersenne twister
    Rnd RandAngle{ 0.0f, 359.0f };  // ângulo aleatório
    Rnd RandColor{ 0.0f, 1.0f };    // cor aleatória
    float upperTime = 0.0f;         // tempo que ela vai ficar indo para cima
	float lifeCount = 0.0f;          // contador de vida da partícula

public:
    BloodParticles(float x, float y);                    // construtor
    ~BloodParticles();                   // destrutor

    int  Size();                    // quantidade de partículas
    void Update();                  // atualização
    void Draw();                    // desenho
};