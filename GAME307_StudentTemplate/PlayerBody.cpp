//
//  PlayerBody.cpp
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#include "PlayerBody.h"
#include "Projectile.h"
Projectile bullet;
std::vector<Projectile> bullets;
GearState& operator+=(GearState& state, int increment) {
    int value = static_cast<int>(state) + increment;
    state = static_cast<GearState>(value % 6); // Ensure the value stays within the range of enum
    return state;
}

GearState& operator-=(GearState& state, int increment) {
    int value = static_cast<int>(state) - increment;
    state = static_cast<GearState>(value % 6); // Ensure the value stays within the range of enum
    return state;
}

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
    gearState = GearState::NEUTRAL;

    playerStats = new ShipStats(50, 100, 0, 0);
    playerAmmo = new ShipAmmo(100,34,7);

    bullet = Projectile();
    bullet.SetGame(game);
  
    bullet.SetPos(Vec3(-500,-500,0));

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
    
    collider.SetColliderBounds(square.w, square.h);
    collider.SetColliderPosition(square.x, square.y);
    collider.RenderCollider(renderer);

    for (int i = 0; i < bullets.size(); i++)
    {

        if (bullets.at(i).GetFiredStatus() == true) bullets.at(i).Render(0.05);

    }

}

void PlayerBody::HandleEvents(const SDL_Event& event)
{
    // if key pressed, set velocity or acceleration

    const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);



        //Change rotation of player with the A and D keys
        //Increase or decrease speed of player with W and S keys
    switch (event.type)
    {
    case SDL_KEYDOWN:
        if (event.key.keysym.scancode == SDL_SCANCODE_W && event.key.repeat == 0)
        {
            if (gearState != GearState::DRIVE3) gearState += 1;
        }

        if (keyboard_state_array[SDL_SCANCODE_A])
        {
            if (gearState != GearState::REVERSE) orientation -= 0.1;
            else orientation += 0.1;

        }

        if (event.key.keysym.scancode == SDL_SCANCODE_S && event.key.repeat == 0)
        {
            if (gearState != GearState::REVERSE) gearState -= 1;

        }

        if (keyboard_state_array[SDL_SCANCODE_D])
        {
            if (gearState != GearState::REVERSE) orientation += 0.1;
            else orientation -= 0.1;

        }


        if (keyboard_state_array[SDL_SCANCODE_SPACE])
        {
            if ((playerAmmo->GetCurrentTotalAmmo() != 0 || playerAmmo->GetCurrentMagAmmo() != 0) && playerAmmo->IsReloading() != true)
            {   
                    
                    
                    bullets.push_back(bullet);
                    bullets.at(bullets.size() - 1).OnCreate();
                    bullets.at(bullets.size() - 1).SetFiredStatus(true);
                    bullets.at(bullets.size() - 1).SetPos(pos + Vec3(-sin(orientation) * speed, -cos(orientation) * speed, 0));
                    bullets.at(bullets.size() - 1).SetProjectileSpeed(10);
                    bullets.at(bullets.size() - 1).SetDirectionVector(Vec3(-sin(orientation), -cos(orientation), 0));
                    playerAmmo->DecreaseCurrentMagAmmo(1);
                    //->SetPos(Vec3(-500, -500, 0));
                    //bullet->SetDirectionVector(Vec3(0,0,0));

            }
        }

        ///Player DEBUG ONLY
            if (keyboard_state_array[SDL_SCANCODE_H])
            {
                playerStats->Heal(7);

            }

            if (keyboard_state_array[SDL_SCANCODE_I])
            {
                playerStats->TakeDamage(7);

            }

            if (keyboard_state_array[SDL_SCANCODE_K])
            {
                playerAmmo->DecreaseCurrentMagAmmo(1);

            }
            if (keyboard_state_array[SDL_SCANCODE_R])
            {
                playerAmmo->Reload();

            }

            if (event.key.keysym.sym == SDLK_2)
            {
                std::cout << "\nPlayer Collider Details\n"
                    << collider.GetColliderRect().x << " " << collider.GetColliderRect().y << " " << collider.GetColliderRect().w << " " << collider.GetColliderRect().h;
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

    /*std::cout << "Ammo: " << playerAmmo->GetCurrentMagAmmo() << "/" << playerAmmo->GetCurrentTotalAmmo() << std::endl;*/
    CalculateSpeed();
    //Acceleration is based on the orientation of the player, player will be moving at all times since they are moving on water
    accel = Vec3(-sin(orientation) * speed, -cos(orientation) * speed, 0);

    for (int i = 0; i < bullets.size(); i++)
    {
       
        if (bullets.at(i).GetFiredStatus() == true)
        {    
            bullets.at(i).Update(deltaTime);
            
        }
       
    }
    playerAmmo->Update(deltaTime);
}

void PlayerBody::resetToOrigin()
{
    pos = Vec3(0.0f + radius, 0.0f + radius, 0.0f);
}

Collider2D PlayerBody::GetCollider()
{
    return collider;
}

void PlayerBody::CalculateSpeed()
{

    if(gearState == GearState::DRIVE3)
    {

        speed = getMaxSpeed();

    }

    if (gearState == GearState::DRIVE2)
    {

        speed = getMaxSpeed() / 2;

    }
    if (gearState == GearState::DRIVE1)
    {

        speed = getMaxSpeed() / 4;

    }

    if (gearState == GearState::NEUTRAL)
    {

        speed = 0.25;

    }

    if (gearState == GearState::PARK)
    {

        speed = 0;

    }

    if (gearState == GearState::REVERSE)
    {

        speed = (getMaxSpeed() / 4) * -1;

    }

    
}
