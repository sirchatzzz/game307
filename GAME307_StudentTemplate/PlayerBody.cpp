//
//  PlayerBody.cpp
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#include "PlayerBody.h"

bool PlayerBody::OnCreate()
{
    image = IMG_Load( "Pacman.png" );
    if (image == nullptr) {
        std::cerr << "Can't open the image" << std::endl;
        return false;
    }
    SDL_Renderer *renderer = game->getRenderer();
    texture = SDL_CreateTextureFromSurface( renderer, image );
    if (!texture)
    {
        std::cerr << "Can't create the texture" << std::endl;
        return false;
    }
    maxAcceleration = 15.0f;
    return true;
}

void PlayerBody::Render( float scale )
{
    // This is why we need game in the constructore, to get the renderer, etc.
    SDL_Renderer *renderer = game->getRenderer();
    Matrix4 projectionMatrix = game->getProjectionMatrix();

    // square represents the position and dimensions for where to draw the image
    SDL_Rect square;
    Vec3 screenCoords;
    float    w, h;

    // convert the position from game coords to screen coords
    screenCoords = projectionMatrix * pos;
    w = image->w * scale;
    h = image->h * scale;

    // The square's x and y values represent the top left corner of
    // where SDL will draw the .png image
    // The 0.5f * w/h offset is to place the .png so that pos represents the center
    // (Note the y axis for screen coords points downward, hence subtractions!!!!)
    square.x = static_cast<int>(screenCoords.x - 0.5f * w);
    square.y = static_cast<int>(screenCoords.y - 0.5f * h);
    square.w = static_cast<int>(w);
    square.h = static_cast<int>(h);

    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI ;

    SDL_RenderCopyEx( renderer, texture, nullptr, &square,
        orientationDegrees, nullptr, SDL_FLIP_NONE );
}

void PlayerBody::HandleEvents( const SDL_Event& event )
{
    // if key pressed, set velocity or acceleration

    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
    {
        switch ( event.key.keysym.scancode )
        {
            case SDL_SCANCODE_W:
                isAccelerating = true;
                accel.y += maxAcceleration * 1.0f;
                break;
            case SDL_SCANCODE_S:
                isAccelerating = true;
                accel.y += maxAcceleration * -1.0f;
                break;
            case SDL_SCANCODE_A:
                isAccelerating = true;
                accel.x += maxAcceleration * -1.0f;
                break;
            case SDL_SCANCODE_D:
                isAccelerating = true;
                accel.x += maxAcceleration * 1.0f;
                break;
            default:
                break;
        }
    }

    // if key is released, stop applying movement

    if( event.type == SDL_KEYUP && event.key.repeat == 0 )
    {
        switch ( event.key.keysym.scancode )
        {
            case SDL_SCANCODE_S:
                isAccelerating = false;
                accel.y = 0.0;
                break;
            case SDL_SCANCODE_W:
                isAccelerating = false;
                accel.y = 0.0;
                break;
            case SDL_SCANCODE_A:
                isAccelerating = false;
                accel.x = 0.0;
                break;
            case SDL_SCANCODE_D:
                isAccelerating = false;
                accel.x = 0.0;
                break;
            default:
                break;
        }
    }
}

void PlayerBody::Update( float deltaTime )
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion

    Body::Update( deltaTime );

    // This will ensure player body stops at edges
    float height, width;
    height = game->getSceneHeight();
    width = game->getSceneWidth();

    if (pos.x < radius)
    {
        pos.x = radius;
        vel.x = 0.0f;
    }
    if (pos.y < radius)
    {
        pos.y = radius;
        vel.y = 0.0f;
    }
    if (pos.x > width-radius)
    {
        pos.x = width - radius;
        vel.x = 0.0f;
    }
    if (pos.y > height-radius)
    {
        pos.y = height - radius;
        vel.y = 0.0f;
    }
}

void PlayerBody::resetToOrigin()
{
    pos = Vec3( 0.0f + radius, 0.0f + radius, 0.0f );
}
