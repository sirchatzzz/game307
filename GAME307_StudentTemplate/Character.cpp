#include "Character.h"
#include "Arrive.h"
#include "Align.h"
bool Character::OnCreate(Scene* scene_)
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
		body = new KinematicBody(
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

	return true;
}

bool Character::setTextureWith(string file)
{
	SDL_Surface* image = IMG_Load(file.c_str());
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture)
	{
		std::cerr << "Can't create texture" << std::endl;
		return false;
	}
	body->setTexture(texture);
}


void Character::Update(float deltaTime)
{
	//Create steering behaviour
	SteeringOutput* steering;
	steering = new SteeringOutput();



	//Find the distance between the AI and its target
	Vec3 distance = target->getPos() - body->getPos();
	//body->setOrientation(std::atan2(distance.x, distance.y) * 170 / M_PI / 50);
	//Check to see if AI is near target
	if (!checkIfNearTarget())
	{
		//Set the radius of the target
		float targetRadius = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
		//Set the slow radius so the AI will begin to slow down once it enters this radius
		float slowRadius = targetRadius + 5;
		//Create an Arrive steering behaviour and set the parameters
		Arrive arrive(body->getMaxAcceleration() + 2, body->getMaxSpeed() + 4, targetRadius, slowRadius);
		//Call arrive function that sets this steering behaviour to the one created in the function
		steering = arrive.getSteering(target->getPos(), this);

		
		Align align(body->getMaxAngular(), body->getMaxRotation(), 1, 1);
		steering->angular = align.getSteering(target->getOrientation(), this);
		
	}

	//Update AI
	body->Update(deltaTime, steering);
	//Delete steering behaviour when finished
	delete steering;



}

void Character::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void Character::render(float scale)
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
}

///Setter for target
void Character::setTarget(PlayerBody* target_)
{
	target = target_;
}


///Basic function to check if the AI is near its target
bool Character::checkIfNearTarget()
{



	Vec3 distance = target->getPos() - body->getPos();
	bool nearTarget;


	if (abs(distance.x) < 3 && abs(distance.y) < 3 && abs(distance.z) < 3) nearTarget = true;
	else nearTarget = false;



	return nearTarget;

}
