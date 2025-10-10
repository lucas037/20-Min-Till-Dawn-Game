#include "DeathParticles.h"
#include "MinutesTillDawn.h"
#include <corecrt_math_defines.h>

DeathParticles::DeathParticles(float x, float y)
{
    Generator starmaker;
    starmaker.imgFile = "Resources/Star.png";   // arquivo de imagem
    starmaker.angle = 90.0f;                    // direção das estrelas
    starmaker.spread = 90.0f;                  // espalhamento em graus
    starmaker.lifetime = 0.8f;                  // tempo de vida (em segundos)
    starmaker.frequency = 0.000f;               // tempo entre geração de novas partículas
    starmaker.percentToDim = 1.0f;              // desaparece após 60% da vida
    starmaker.minSpeed = 15.0f;                 // velocidade mínima das partículas
    starmaker.maxSpeed = 40;                // velocidade máxima das partículas
    starmaker.color.r = 1;
    starmaker.color.g = 0;
    starmaker.color.b = 0;
    starmaker.color.a = 1.0f;                   // transparência da partícula

    upperTime = starmaker.lifetime / 2;
    lifeCount = 0.0f;

    pGen = new Particles(starmaker);
    pGen->Generate(x, y, 9);

    Generator starmaker2;
    starmaker2.imgFile = "Resources/Star.png";   // arquivo de imagem
    starmaker2.angle = 90.0f;                    // direção das estrelas
    starmaker2.spread = 90.0f;                  // espalhamento em graus
    starmaker2.lifetime = 0.8f;                  // tempo de vida (em segundos)
    starmaker2.frequency = 0.000f;               // tempo entre geração de novas partículas
    starmaker2.percentToDim = 1.0f;              // desaparece após 60% da vida
    starmaker2.minSpeed = 10.0f;                 // velocidade mínima das partículas
    starmaker2.maxSpeed = 20;                // velocidade máxima das partículas
    starmaker2.color.r = 0.7f;
    starmaker2.color.g = 0.7f;
    starmaker2.color.b = 0.7f;
    starmaker2.color.a = 1.0f;                   // transparência da partícula

    upperTime = starmaker2.lifetime / 2;
    lifeCount = 0.0f;

    pGen2 = new Particles(starmaker2);
    pGen2->Generate(x + 10, y + 10, 9);
}

DeathParticles::~DeathParticles()
{
    delete pGen;
	delete pGen2;
}

void DeathParticles::Update()
{
    pGen->Update(gameTime);
    pGen2->Update(gameTime);

    if (pGen->Inactive())
        MinutesTillDawn::scene->Delete();

    if (pGen2->Inactive())
		MinutesTillDawn::scene->Delete();
}


inline int DeathParticles::Size()
{
    return pGen->Size();
}

inline void DeathParticles::Draw()
{
    pGen->Draw(Layer::MIDDLE, 1.5f);
	pGen2->Draw(Layer::MIDDLE, 1.5f);
}