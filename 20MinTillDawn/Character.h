#pragma once

#include "Object.h"                        // objetos do jogo
#include "Sprite.h"                        // desenho de sprites
#include "Animation.h"
#include "Vector.h"                        // representação de vetores
#include "Particles.h"                    // sistema de partículas
#include "Heart.h"
using namespace std;

enum charAnim { STOP, RUNNIG, WALKING };

// ---------------------------------------------------------------------------------

class Character : public Object
{
private:
	TileSet* tileset;
    Animation* anim;  
    Particles* particles;   
	bool right;           
    float timeCounter = 0.0f;
    float invincibilityTime = 1.5f;
    bool isInvincible = false;

public:
    Vector* speed;    
    uint lifePoints;
    uint maxLifePoints;
    vector<Heart*> hearts;

    Character();                         
    ~Character();                       

    void Damage();
    void Move();            
    void Update();                      
    void Draw();        

    void OnCollision(Object* obj);
};