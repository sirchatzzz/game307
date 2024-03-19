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
#include "ShipStats.h"
#include "Projectile.h"
#include <vector>
#include "Turret.h"

//Enum for gear states
enum GearState {

     REVERSE = 0,
     PARK = 1,
     NEUTRAL = 2,
     DRIVE1 = 3,
     DRIVE2 = 4,
     DRIVE3 = 5
};

class Projectile;

class PlayerBody : public Body
{
protected:
    class GameManager* game;

    //Collider object
    Collider2D collider;

    //Gear states
    GearState gearState;

    //Ship stats for player
    ShipStats* playerStats;
    ShipAmmo* playerAmmo;
    int currentMagTemp = 0; // To hold current mag

    //Turret object
    class Turret* turret;

    //Bullet vector
    class std::vector<Projectile> bullets;


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
    {}
    
    //Base functions for each class
    bool OnCreate();
    void Render( float scale = 1.0f );
    void HandleEvents( const SDL_Event& event );
    void Update( float deltaTime );
    void resetToOrigin();
    void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    
    //Getter for collider
    Collider2D GetCollider();

    //Calculate speed for player
    void CalculateSpeed();

    //Getters for player stats and info
    GearState GetGearState() { return gearState; }
    ShipStats* GetPlayerStats() { return playerStats; }
    ShipAmmo* GetPlayerAmmo() { return playerAmmo; }

    //Getter for bullets
    std::vector<Projectile>* GetBullets() { return &bullets; }

    //Function to fire bullets
    void FireBullet();

};

#endif /* PLAYERBODY_H */
