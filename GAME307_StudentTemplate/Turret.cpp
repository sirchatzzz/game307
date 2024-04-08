
#include "Turret.h"

bool Turret::OnCreate(){
    frameCounter = 0;
    turretImage = IMG_Load("assets/cannonIdle.png");
    if (turretImage == nullptr) {
        std::cerr << "Can't open the image" << std::endl;
        return false;
    }
    SDL_Renderer* renderer = game->getRenderer();
    texture = SDL_CreateTextureFromSurface(renderer, turretImage);
    if (!texture)
    {
        std::cerr << "Can't create the texture" << std::endl;
        return false;
    }


    return true;
}

void Turret::OnDestroy()
{

    delete this;
}

void Turret::Render(float scale)
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

    w = 64;
    h = 64;

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

}


void Turret::Update(float deltaTime)
{
    ++frameCounter;
    if (frameCounter > 30)
    {
        SetTurretImage("assets/cannonIdle.png");
        frameCounter = 0;
    }

    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion

    Body::Update(deltaTime);
}

void Turret::resetToOrigin()
{
    pos = Vec3(0.0f + radius, 0.0f + radius, 0.0f);
}

void Turret::SetTurretImage(const char* path)
{
    turretImage = IMG_Load(path);
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* newTexture;
    newTexture = SDL_CreateTextureFromSurface(renderer, turretImage);
    if (newTexture != nullptr) texture = newTexture;
}
