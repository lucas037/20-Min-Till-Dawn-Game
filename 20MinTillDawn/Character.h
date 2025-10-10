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
    
	uint xpPoints = 0;
    uint pointsToNextLevel = 0;
	uint level = 1;
    
    float timeCounter = 0.0f;
    float invincibilityTime = 0.5f;
    float maxSpeed = 0.0f;
    bool isInvincible = false;
    bool isStunned = false;
    float stunTimer = 0.0f;
    const float stunDuration = 0.3f;

    float shootTimer = 0.0f;
    const float shootDuration = 0.4f;

    // walk timer
    bool walkingSongActive = false;
	float walkTimer = 0.0f;
	const float walkDuration = 0.35f;

    bool lowHp = false;
	bool isShooting = false;
    
    float shootingSpeed = 0.0f;
	float normalSpeed = 0.0f;

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
    void AddHeart();
    void AddMaxHeart();

    void OnCollision(Object* obj);

	void AddExperience();

    void shoot(bool shooting);
};