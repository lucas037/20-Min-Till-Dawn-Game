#pragma once

#include "Game.h"
#include "Sprite.h"

class InitialMenu : public Game {
	private:	
		Sprite* background = nullptr;

	public:
		void Init();
		void Update();
		void Draw();
		void Finalize();
};