#include "Character.h"
#include "Arrive.h"
#include "Align.h"
#include "Evade.h"
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>
#include "FollowAPath.h"

Projectile bullet2;


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

	collider.SetColliderActive(true);

	aggroRadius = 4;
	attackRadius = 2;
	bullet2 = Projectile();
	bullet2.SetGame(scene->game);

	CalculateTargetIsland();

	turret = new Turret();
	turret->SetGame(scene->game);
	turret->OnCreate();
	attackSpeed = 80;
	target = Vec3();
	patrolling = false;
	animationCounter = 0;
	return true;
}

bool Character::setImageWith(SDL_Surface** images_, int spriteIndex_)
{
	spriteImages = images_;

	if (spriteImages[spriteIndex_] == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, spriteImages[spriteIndex_]);
	if (!texture)
	{
		std::cerr << "Can't create texture" << std::endl;
		return false;
	}
	body->setTexture(texture);
}


void Character::Update(float deltaTime)
{
	if (enemyStats->GetHealth() == 0) EnemyDeath();
	
	if (targetIsland.IsDestroyed()) CalculateNextIsland();

	CalculateState();
	
	static float time = 0;
	++animationCounter;
	if (animationCounter > 60) animationCounter = 0;
	int indexSelector = std::round(animationCounter / 20.0f);
	setImageWith(spriteImages, indexSelector);

	//Pathfind and steer to target island
	if (enemyState == AIState::GOTOISLAND)
	{




	}

	//Pathfind and steer to target player
	if (enemyState == AIState::CHASEPLAYER)
	{




	}

	//Attack Target
	if (enemyState == AIState::ATTACKTARGET)
	{

		time++;
		if (time > attackSpeed)
		{

			FireBullet();

				time = 0;
		}


	}

	//////Create steering behaviour
	//SteeringOutput* steering;
	//steering = new SteeringOutput();
	//static float time = 0;

	////Find the distance between the AI and its target
	//Vec3 distance = target - body->getPos();

	////Change Orientation of Character
	//Align align;
	//FollowAPath followAPath;
	//*steering += *(align.getSteering(target, this));

	//time = 0;
	////Set the radius of the target
	//float targetRadius = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	////Set the slow radius so the AI will begin to slow down once it enters this radius
	//float slowRadius = targetRadius + 5;
	////Create an Arrive steering behaviour and set the parameters
	//Arrive arrive(body->getMaxAcceleration(), body->getMaxSpeed(), targetRadius, slowRadius);
	////Call arrive function that sets this steering behaviour to the one created in the function
	//
	//if (currentPath.GetCurrentNode() != NULL && characterPath.GetCurrentNode() != NULL)
	//{

	//	std::cout << "Current Path: " << currentPath.GetCurrentNode()->getLabel() << " Patrol Path Start Node: " << characterPath.GetCurrentNode()->getLabel() << "\n";
	//	//if (!patrolling && abs(body->getPos().x) - abs(currentPath.GetCurrentNode()->GetPos().x) < 1.8f && abs(body->getPos().y) - abs(currentPath.GetCurrentNode()->GetPos().y) < 1.8f)
	//	if(!patrolling && currentPath.GetCurrentNode() != characterPath.GetCurrentNode())
	//	{
	//		*steering += *(followAPath.getSteering(&currentPath, this));			
	//	}
	//	else
	//	{
	//		patrolling = true;
	//		*steering += *(followAPath.getSteering(&characterPath, this));
	//	}
	//		
	//}
	//


	////Check to see if AI is near target
	//if (!checkIfNearTarget())
	//{
	//	
	//	

	//	//near = true;
	//	
	//}
	//else
	//{
	//	//If near player then Fire
	//	time++;
	//	if (time > attackSpeed)
	//	{

	//		FireBullet();

	//		time = 0;
	//	}

	//}

	//
	////Steering
	//if (sqrt(distance.x * distance.x + distance.y * distance.y) < aggroRadius)
	//{
	//

	//	

	//}
	////If not steering towards target instead use path finding to patrol map
	//else
	//{

	//}



	////Update AI
	//body->Update(deltaTime,steering);

	////Delete steering behaviour when finished
	//delete steering;

	//Update turret and bullets
	UpdateTurret(deltaTime);
	UpdateBullets(deltaTime);

}

void Character::HandleEvents(const SDL_Event& event)
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

	collider.SetColliderBounds(square.w, square.h);
	collider.SetColliderPosition(square.x, square.y);
	collider.RenderCollider(renderer);

	turret->Render(1);

	for (int i = 0; i < bullets.size(); i++)
	{

		if (bullets.at(i).GetFiredStatus() == true) bullets.at(i).Render(0.05);

	}

}

///Basic function to check if the AI is near its target
bool Character::checkIfNearTarget()
{

	Vec3 distance = target - body->getPos();
	bool nearTarget;

	if (sqrt(distance.x * 2 + distance.y * 2 + distance.z * 2) < attackRadius) nearTarget = true;
	else nearTarget = false;

	return nearTarget;

}

Collider2D Character::GetCollider()
{
	return collider;
}


void Character::SetCharacterPath(Path path_)
{
	characterPath.SetPath(path_.GetPath());
	
}

//Update the turret object 
void Character::UpdateTurret(float deltaTime_)
{


	turret->setPos(body->getPos());

	//Match orientation to the AI's orientation if the AI is not close enough to attack player
	if (!checkIfNearTarget()) turret->SetOrientation(body->getOrientation());
	//If the AI is close enough to attack then change the turret orientation to be where the player is
	else
	{
		Vec3 distance = target - turret->getPos();
		turret->SetOrientation(std::atan2(-distance.x, -distance.y));


	}



	turret->Update(deltaTime_);

}

//Update bullets 
void Character::UpdateBullets(float deltaTime_)
{

	for (int i = 0; i < bullets.size(); i++)
	{

		if (bullets.at(i).GetFiredStatus() == true)
		{
			bullets.at(i).Update(deltaTime_);

		}

	}

}

//Create and fire bullets
void Character::FireBullet()
{

	//Push back bullet and set the necessary variables
	bullets.push_back(bullet2);
	bullets.at(bullets.size() - 1).OnCreate();
	bullets.at(bullets.size() - 1).SetFiredStatus(true);
	bullets.at(bullets.size() - 1).SetPos(body->getPos() + Vec3(-sin(turret->getOrientation()), -cos(turret->getOrientation()), 0) * 0.5);
	bullets.at(bullets.size() - 1).SetProjectileSpeed(10);
	bullets.at(bullets.size() - 1).SetProjectileDamage(enemyStats->GetWeaponDamage());

	//Work In Progress; Create an offset for the bullet so it fires slighty to the left or right so the shooting isn't 100% accurate
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define the range
	float lower_bound = -0.25;
	float upper_bound = 0.25;

	// Create a distribution
	std::uniform_int_distribution<> distr(lower_bound, upper_bound);

	// Generate and print a random number within the range
	float random_number = distr(gen);

	//Set direction vector for the bullet to move towards
	bullets.at(bullets.size() - 1).SetDirectionVector(Vec3(-sin(turret->getOrientation()) + random_number, -cos(turret->getOrientation()) + random_number, 0));

}

bool Character::IsCharacterAtPos(Vec3 pos_)
{
	if (body->getPos() != pos_)
	{
		//setTarget(pos_);
		return false;
	}

	return true;
}

void Character::EnemyDeath()
{
	std::cout << "Is Dead" << std::endl;
	isDead = true;

}

void Character::CalculateState()
{
	Vec3 distanceToPlayerVector = targetPlayer.getPos() - getBody()->getPos();
	float distanceToPlayer = sqrt(distanceToPlayerVector.x * 2 + distanceToPlayerVector.y * 2 + distanceToPlayerVector.z * 2);



	if (distanceToPlayer > aggroRadius)
	{

		enemyState = AIState::GOTOISLAND;
		target = targetIsland.getBody()->getPos();


	}

	if (distanceToPlayer < aggroRadius)
	{
		enemyState = AIState::CHASEPLAYER;
		target = targetPlayer.getPos();

	}

	Vec3 distanceToTargetVector = target - getBody()->getPos();
	float distanceToTarget = sqrt(distanceToTargetVector.x * 2 + distanceToTargetVector.y * 2 + distanceToTargetVector.z * 2);

	if (distanceToTarget < attackRadius) enemyState = AIState::ATTACKTARGET;
	else
	{
		if (target = targetPlayer.getPos()) enemyState = AIState::CHASEPLAYER;


	}


}

void Character::CalculateTargetIsland()
{

	Vec3 distanceVector;
	float distance;


	for (int i = 0; i < islands.size(); i++)
	{

		distanceVector = islands.at(i).getBody()->getPos() - getBody()->getPos();
		float d = sqrt(distanceVector.x * 2 + distanceVector.y * 2 + distanceVector.z * 2);

		if (i == 0)
		{
			distance = d;
			targetIsland = islands.at(0); 
		}
		if (d < distance)
		{
			distance = d;
			targetIsland = islands.at(i);


		}
	}


}

void Character::CalculateNextIsland()
{

	auto it = std::find(islands.begin(), islands.end(), targetIsland);

	if (it != islands.end()) {

		islands.erase(it);

	}

	CalculateTargetIsland();

}



