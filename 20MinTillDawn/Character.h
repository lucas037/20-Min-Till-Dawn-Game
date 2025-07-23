#pragma once

#include "Object.h"                        // objetos do jogo
#include "Sprite.h"                        // desenho de sprites
#include "Animation.h"
#include "Vector.h"                        // representação de vetores
#include "Particles.h"                    // sistema de partículas
#include "Controller.h"
#include "Heart.h"
using namespace std;

enum charAnim { STOP, RUNNIG, WALKING };

// ---------------------------------------------------------------------------------

class Character : public Object
{
protected:
	TileSet* tileset;
    Animation* anim;  
    Particles* particles;   
	bool right;           
    float timeCounter = 0.0f;
    float invincibilityTime = 1.5f;
    float maxSpeed = 0.0f;
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

    void HandleXboxInput(float& dx, float& dy);
    void HandleGenericControllerInput(float& dx, float& dy);
    void HandleKeyboardInput(float& dx, float& dy);
    void UpdateAnimationDirection(float dx);
    void UpdateMovement(float dx, float dy);
    void StartHearts();

    void OnCollision(Object* obj);
};