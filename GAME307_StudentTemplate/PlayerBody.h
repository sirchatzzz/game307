//
//  PlayerBody.h
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include <stdio.h>
#include "Body.h"
#include "GameManager.h"
#include "Collider2D.h"

enum GearState {

     REVERSE = 0,
     PARK = 1,
     NEUTRAL = 2,
     DRIVE1 = 3,
     DRIVE2 = 4,
     DRIVE3 = 5
};



class PlayerBody : public Body
{
protected:
    class GameManager* game;
    bool isAccelerating;
    Collider2D collider;
    GearState gearState;


public:
    PlayerBody() : Body{}
    {
        game = nullptr;
    }

    PlayerBody(
        Vec3 pos_, Vec3 vel_, Vec3 accel_,
        float mass_,
        float radius_,
        float orientation_,
        float rotation_,
        float angular_,
        float maxSpeed_,
        float maxAcceleration_,
        float maxRotation_,
        float maxAngular_,
        GameManager *game_
    ) : Body{
          pos_
        , vel_
        , accel_
        , mass_
        , radius_
        , orientation_
        , rotation_
        , angular_
        , maxSpeed_
        , maxAcceleration_
        , maxRotation_
        , maxAngular_
    }
        , game{ game_ }
        , isAccelerating(false)
    {}
    
    // use the base class versions of getters

    bool OnCreate();
    void Render( float scale = 1.0f );
    void HandleEvents( const SDL_Event& event );
    void Update( float deltaTime );
    void resetToOrigin();
    void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    
    Collider2D GetCollider();

    void CalculateSpeed();
    GearState GetGearState() { return gearState; }
    void IncreaseO() { orientation -= 0.05; }
};

#endif /* PLAYERBODY_H */
