#include "Island.h"
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>


bool Island::OnCreate(Scene* scene_)
{
	scene = scene_;
	// Configure and instantiate the body to use for the demo
	if (!body)
	{
		float radius = 0.2;
		float orientation = 0.0f;
		float rotation = 0.0f;
		float angular = 0.0f;
		float maxSpeed = 4.0f;
		float maxAcceleration = 10.0f;
		float maxRotation = 2.0f;
		float maxAngular = 10.0f;
		body = new Body(
			Vec3(10.0f, 5.0f, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), 1.0f,
			radius,
			orientation,
			rotation,
			angular,
			maxSpeed,
			maxAcceleration,
			maxRotation,
			maxAngular
		);
	}

	if (!body)
	{
		return false;
	}

	stats = new Stats(100, 100, 0);

	collider.SetColliderActive(true);

	return true;
}

bool Island::setImageWith(SDL_Surface* file)
{
	SDL_Surface* image = file;
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture)
	{
		std::cerr << "Can't create texture" << std::endl;
		return false;
	}
	body->setTexture(texture);
}


void Island::Update(float deltaTime)
{
	if (stats->GetHealth() == 0) body->setTexture(texture);
}

void Island::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
	switch (event.type)
	{
	case SDL_KEYDOWN:
		
		if (event.key.keysym.sym == SDLK_2)
		{
			
		}
		break;
	}
}

void Island::render(float scale)
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int    w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(body->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * body->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees.
	float orientation = body->getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, body->getTexture(), nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);
	
	collider.SetColliderBounds(square.w, square.h);
	collider.SetColliderPosition(square.x, square.y);
	collider.RenderCollider(renderer);

}

Collider2D Island::GetCollider()
{
	return collider;
}

