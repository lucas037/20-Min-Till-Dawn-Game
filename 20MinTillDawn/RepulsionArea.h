#pragma once

#include "Object.h"    
#include "character.h"

// ---------------------------------------------------------------------------------
// Classe auxiliar para quando o personagem é atingido
// ---------------------------------------------------------------------------------

class RepulsionArea : public Object
{
private:
    float timeCounter = 0.0f;
    float duration = 0.5f;
	float intensity = 100.0f;
	Character* character = nullptr; // Pointer to the character that caused the repulsion

public:
    RepulsionArea(float x, float y);
    RepulsionArea(Character * character);
    ~RepulsionArea();
    void Update();
    void Draw();

	float Intensity() const { return intensity; }
};