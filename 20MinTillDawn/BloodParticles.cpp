#include "BloodParticles.h"
#include "MinutesTillDawn.h"
#include <corecrt_math_defines.h>

BloodParticles::BloodParticles(float x, float y)
{
    Generator starmaker;
    starmaker.imgFile = "Resources/Star.png";   // arquivo de imagem
    starmaker.angle = 90.0f;                    // dire��o das estrelas
    starmaker.spread = 140.0f;                  // espalhamento em graus
    starmaker.lifetime = 0.5f;                  // tempo de vida (em segundos)
    starmaker.frequency = 0.000f;               // tempo entre gera��o de novas part�culas
    starmaker.percentToDim = 1.0f;              // desaparece ap�s 60% da vida
    starmaker.minSpeed = 80.0f;                 // velocidade m�nima das part�culas
    starmaker.maxSpeed = 100.0f;                // velocidade m�xima das part�culas
    starmaker.color.r = 1;          
    starmaker.color.g = 0;      
    starmaker.color.b = 0;          
    starmaker.color.a = 1.0f;                   // transpar�ncia da part�cula

    upperTime = starmaker.lifetime / 2;
    lifeCount = 0.0f;

    starGen = new Particles(starmaker);
    starGen->Generate(x, y, 18);
}

BloodParticles::~BloodParticles()
{
    delete starGen;
}

void BloodParticles::Update()
{
    starGen->Update(gameTime);

    for (int i = 0; i < starGen->Size() / 2; ++i)
    {
        Particle* p = starGen->Get(i);

        p->speed.Rotate(-60 * gameTime);
    }

    for (int i = starGen->Size() / 2; i < starGen->Size(); ++i)
    {
        Particle* p = starGen->Get(i);

        p->speed.Rotate(60 * gameTime);
    }

    if (starGen->Inactive())
        MinutesTillDawn::scene->Delete();
}


inline int BloodParticles::Size()
{
    return starGen->Size();
}

inline void BloodParticles::Draw()
{
    starGen->Draw(Layer::MIDDLE, 1.5f);
}