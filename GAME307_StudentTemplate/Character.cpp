#include "Character.h"

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;
	speed = 0;
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
	// create a new overall steering output
	SteeringOutput* steering;
	steering = new SteeringOutput(Vec3(0.0f, 0.0f, 0.0f), 0);

	steerTo(target, speed, steering);
	body->Update(deltaTime, steering);
	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	// using the target, calculate and set values in the overall steering output

	// apply the steering to the equations of motion


	// clean up memory
	// (delete only those objects created in this function)


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

void Character::setTarget(Vec3 target_)
{

	target = target_;


}

void Character::steerTo(Vec3 target_, float speed_, SteeringOutput* steering_)
{
	if (!checkIfNearTarget())
	{
		setSpeed(2);

		Vec3 distance = target_ - body->getPos();
		distance.x *= speed_;
		distance.y *= speed_;
		distance.z *= speed_;

		steering_->linear = distance;


	}
	else
	{

		body->setVel(Vec3(0.0f, 0.0f, 0.0f));
		body->setAccel(Vec3(0.0f, 0.0f, 0.0f));


	}
}

bool Character::checkIfNearTarget()
{

	Vec3 distance = target - body->getPos();

	if (distance.x < 0) distance.x *= -1;
	if (distance.y < 0) distance.y *= -1;
	if (distance.z < 0) distance.z *= -1;

	bool nearTarget;

	if (distance.x < 3 && distance.y < 3 && distance.z < 3) nearTarget = true;
	else nearTarget = false;



	return nearTarget;



}
