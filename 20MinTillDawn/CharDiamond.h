#pragma once
#pragma once

#include "Character.h"
#include "MinutesTillDawn.h"

// ---------------------------------------------------------------------------------
class CharDiamond : public Character
{
private:

public:
	CharDiamond();
	~CharDiamond();

	void OnCollision(Object* obj) override;
	void Update() override;
};