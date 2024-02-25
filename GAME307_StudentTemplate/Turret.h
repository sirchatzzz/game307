
#ifndef TURRET_H
#define TURRET_H

#include <stdio.h>
#include "Body.h"
#include "GameManager.h"


class Turret : public Body
{
protected:
    class GameManager* game;

public:
    Turret() : Body{}
    {
        game = nullptr;
    }

    Turret(
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
    
    // use the base class versions of getters

    bool OnCreate();
    void Render( float scale = 1.0f );

    void Update( float deltaTime );
    void resetToOrigin();
    void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    void SetGame(GameManager* game_) { game = game_; }
};

#endif
