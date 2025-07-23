#pragma once

#include "Character.h"
#include "MinutesTillDawn.h"

// ---------------------------------------------------------------------------------
class CharShana : public Character
{
private:

public:
	CharShana();
	~CharShana();

	void OnCollision(Object* obj) override;
	void Update() override;
};