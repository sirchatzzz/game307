
#include "Projectile.h"

Projectile::~Projectile()
{
    render = false;
}

bool Projectile::OnCreate()
{
    image = IMG_Load("assets/island5.png");
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

    time = 0;
    render = true;

    return true;
}

void Projectile::Render(float scale)
{
    if (render == true)
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
        //collider.RenderCollider(renderer);
    }
}

void Projectile::HandleEvents(const SDL_Event& event)
{

   

}

void Projectile::Update(float deltaTime)
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion
    
    time += deltaTime;
    Body::Update(deltaTime);

    if (time > 10)
    {
        this->~Projectile();
    }

    vel = direction * projectileSpeed;

}

void Projectile::resetToOrigin()
{
    pos = Vec3(0.0f + radius, 0.0f + radius, 0.0f);
}

Collider2D Projectile::GetCollider()
{
    return collider;
}


