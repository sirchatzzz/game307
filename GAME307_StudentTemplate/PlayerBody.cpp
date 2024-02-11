//
//  PlayerBody.cpp
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#include "PlayerBody.h"

bool PlayerBody::OnCreate()
{
    image = IMG_Load("Pacman.png");
    if (image == nullptr) {
        std::cerr << "Can't open the image" << std::endl;
        return false;
    }
    SDL_Renderer* renderer = game->getRenderer();
    texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture)
    {
        std::cerr << "Can't create the texture" << std::endl;
        return false;
    }

    collider.SetColliderActive(true);

    return true;
}

void PlayerBody::Render(float scale)
{
    // This is why we need game in the constructore, to get the renderer, etc.
    SDL_Renderer* renderer = game->getRenderer();
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
    float orientationDegrees = orientation * 180.0f / M_PI;

    SDL_RenderCopyEx(renderer, texture, nullptr, &square,
        orientationDegrees, nullptr, SDL_FLIP_NONE);
    
    collider.SetColliderBounds(w, h);
    collider.SetColliderPosition(screenCoords.x-(w/2), screenCoords.y-(h/2));
    collider.RenderCollider(renderer);

}

void PlayerBody::HandleEvents(const SDL_Event& event)
{
    // if key pressed, set velocity or acceleration

    switch (event.type)
    {
    case SDL_KEYDOWN:
    //Change rotation of player with the A and D keys
    //Increase or decrease speed of player with W and S keys
        if (event.key.keysym.sym == SDLK_w)
        {
            speed += 1;
        }
        if (event.key.keysym.sym == SDLK_a)
        {
            orientation -= 0.05;
        }
        if (event.key.keysym.sym == SDLK_s)
        {
            speed -= 1;
        }
        if (event.key.keysym.sym == SDLK_d)
        {
            orientation += 0.05;
        }
        break;
    }
}

void PlayerBody::Update(float deltaTime)
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion

    Body::Update(deltaTime);

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
    if (pos.x > width - radius)
    {
        pos.x = width - radius;
        vel.x = 0.0f;
    }
    if (pos.y > height - radius)
    {
        pos.y = height - radius;
        vel.y = 0.0f;
    }

    //IF speed is less than 0, set it to 0
    if (speed < 0) speed = 0;
    //IF speed is equal to 0, then set it to a base speed value
    if (speed == 0) speed = 0.15;
    //IF speed is greater than maxSpeed, set speed to equal maxSpeed
    if (speed > maxSpeed) speed = maxSpeed;
    //Acceleration is based on the orientation of the player, player will be moving at all times since they are moving on water
    accel = Vec3(-sin(orientation) * speed, -cos(orientation) * speed, 0);

}

void PlayerBody::resetToOrigin()
{
    pos = Vec3(0.0f + radius, 0.0f + radius, 0.0f);
}

Collider2D PlayerBody::GetCollider()
{
    return collider;
}
