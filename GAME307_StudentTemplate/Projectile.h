#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdio.h>
#include "Body.h"
#include "GameManager.h"
#include "Collider2D.h"
#include "Timer.h"
class Projectile : public Body
{
protected:
    class GameManager* game;
    Collider2D collider;
    float time;
    bool shotFired;
    Vec3 direction;
    bool render;
    float projectileSpeed;
public:
    Projectile() : Body{}
    {
        game = nullptr;
    }

    Projectile(
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
    ~Projectile();
    // use the base class versions of getters

    bool OnCreate();
    void Render( float scale = 1.0f );
    void HandleEvents( const SDL_Event& event );
    void Update( float deltaTime );
    void resetToOrigin();
    void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    void SetGame(GameManager* game_) { game = game_; }
    void SetPos(Vec3 pos_) { pos = pos_; }
    void SetVel(Vec3 vel_) { vel = vel_; }
    void SetDirectionVector(Vec3 direction_) { direction = direction_; }
    Collider2D GetCollider();
    bool GetFiredStatus() { return shotFired; }
    void SetFiredStatus(bool firedStatus_) {shotFired = firedStatus_;}
    void SetProjectileSpeed(float projectileSpeed_) { projectileSpeed = projectileSpeed_; }
    float GetProjectileSpeed() { return projectileSpeed; }
};

#endif
