#pragma once

#include "Object.h"    
#include "character.h"
#include "MinutesTillDawn.h"

// ---------------------------------------------------------------------------------
// Classe auxiliar para quando o personagem é atingido
// ---------------------------------------------------------------------------------

class AttractionArea : public Object
{
private:
	float width = 0.0f;
	float height = 0.0f;
	float attractionForce = 0.0f;

public:
	Character* character = nullptr;

    AttractionArea(Character* character);
    void Update();
	void Draw();

	float AttractionForce();
};