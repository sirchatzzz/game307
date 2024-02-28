#include "Character.h"
#include "Arrive.h"
#include "Align.h"
#include "Evade.h"
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>
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

	aggroRadius = 6;
	
	bullet2 = Projectile();
	bullet2.SetGame(scene->game);

	enemyStats = new ShipStats(100, 100, 5);
	turret = new Turret();
	turret->SetGame(scene->game);
	turret->OnCreate();
	attackSpeed = 80;

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
	////Create steering behaviour
	SteeringOutput* steering;
	steering = new SteeringOutput();
	static float time = 0;



	//Find the distance between the AI and its target
	Vec3 distance = target - body->getPos();

	if (sqrt(distance.x * distance.x + distance.y * distance.y) < aggroRadius)
	{
	

		//Check to see if AI is near target
		if (!checkIfNearTarget())
		{

			//Change Orientation of Character
			Align align;
			*steering += *(align.getSteering(target, this));

			time = 0;
			//Set the radius of the target
			float targetRadius = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
			//Set the slow radius so the AI will begin to slow down once it enters this radius
			float slowRadius = targetRadius + 5;
			//Create an Arrive steering behaviour and set the parameters
			Arrive arrive(body->getMaxAcceleration(), body->getMaxSpeed(), targetRadius, slowRadius);
			//Call arrive function that sets this steering behaviour to the one created in the function
			*steering += *(arrive.getSteering(target, this));

			//near = true;
		}
		else
		{
			//If near player then Fire
			time++;
			if (time > attackSpeed)
			{

				FireBullet();

				time = 0;
			}

		}
		//else
		//{

		//	//Avoid collision with player
		//	if (near == true)
		//	{
		//		double x = target.x;

		//		if (x < body->getPos().x) x = body->getAccel().x + 4;

		//		if (x >= body->getPos().x) x = body->getAccel().x - 4;

		//		double y = target.y;

		//		if (y < body->getPos().y) y = body->getAccel().y - 4;

		//		if (y >= body->getPos().y) y = body->getAccel().y + 4;

		//		nearTargetAccel = Vec3(x, y, 0);
		//		near = false;
		//	}


		//	time++;
		//	if (time > 30) nearTargetAccel = Vec3(0, 0, 0);
		//	steering->linear = nearTargetAccel;
		//}
	}
	//If not steering towards target instead use path finding to patrol map
	else
	{
		//Calculate Tiles and move towards nearest one
		PathfindTiles();


		body->setVel(Vec3(-sin(body->getOrientation()), -cos(body->getOrientation()), 0));
	}



	//Update AI
	body->Update(deltaTime,steering);

	//Delete steering behaviour when finished
	delete steering;

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
			std::cout << "\Character Collider Details\n"
				<< collider.GetColliderRect().x << " " << collider.GetColliderRect().y << " " << collider.GetColliderRect().w << " " << collider.GetColliderRect().h;
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

	turret->Render(scale / 2);

	for (int i = 0; i < bullets.size(); i++)
	{

		if (bullets.at(i).GetFiredStatus() == true) bullets.at(i).Render(0.05);

	}

}

///Setter for target
void Character::setTarget(Vec3 target_)
{
	target = target_;
}


///Basic function to check if the AI is near its target
bool Character::checkIfNearTarget()
{

	Vec3 distance = target - body->getPos();
	bool nearTarget;

	if (abs(distance.x) < 2 && abs(distance.y) < 2 && abs(distance.z) < 2) nearTarget = true;
	else nearTarget = false;

	return nearTarget;

}

Collider2D Character::GetCollider()
{
	return collider;
}

void Character::IslandAvoidance()
{
	for (int i = 0; i < islandColliders.size(); i++)
	{
		if (collider.CollisionCheck(islandColliders[i]))
		{
			Vec3 islandPos;
			islandPos.x = islandColliders[i].GetColliderRect().x;
			islandPos.y = islandColliders[i].GetColliderRect().y;

			Vec3 distance{ 100,100,0 };

			Vec3 reflect = VMath::reflect(body->getPos() +distance, islandPos);

			setTarget(reflect);
		}

	}

}

//Calculate the nearest 9 tiles to the AI
void Character::CalculateTiles()
{
	//Clear the closest tiles vector if it isn't empty
	if (closeTiles.size() > 0) closeTiles.clear();

	std::vector<float>tilesDistance;
	std::vector<Tiles> tilesNew;

	//Run through each tile in the scene and push back the distance between the AI and the Tile 
	for (int i = 0; i < tiles.size(); i++)
	{
		Vec3 distanceVector = tiles.at(i).GetPos() - body->getPos();

		float distance = sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);
		
		tilesDistance.push_back(distance);
		tilesNew.push_back(tiles.at(i));


	}

	//Run through each tile's distance and find the 9 closest tiles to the AI and push those 9 tiles into another vector
	for (int i = 0; i < 9; i++)
	{
		float min_element = std::numeric_limits<float>::max(); // Initialize with maximum possible value
		size_t min_index = 0;

		auto min_it = std::min_element(tilesDistance.begin(), tilesDistance.end());
		// Iterate through the vector to find the minimum element and its index
		for (size_t i = 0; i < tilesDistance.size(); ++i) {
			if (tilesDistance[i] < min_element) {
				min_element = tilesDistance[i];
				min_index = i;
				tile = tilesNew.at(i);


			}
		}

		closeTiles.push_back(tile);

		size_t index = std::distance(tilesDistance.begin(), min_it);
		auto erase_it = std::next(tilesNew.begin(), index);
		tilesDistance.erase(min_it);
		tilesNew.erase(erase_it);
	}

	resetTileCheck = true;
}

void Character::PathfindTiles()
{

	//Calculate closest tiles if it hasn't been calculated yet
	if (resetTileCheck != true) CalculateTiles();

	//Run through the 9 closes tiles except for the current tile the AI is on and the tile the AI was previously on and check to see what the closest tile that is able to be entered
	for (int i = 0; i < closeTiles.size(); i++)

	{
		if (closeTiles.at(i).GetID() != currentTile.GetID())
		{
			if (closeTiles.at(i).GetID() != previousTile.GetID())
			{
			
					if (closeTiles.at(i).TileStatus())
					{

						targetTile = closeTiles.at(i);
						break;

					}
				
			}
		}
		
	}
	
	//Set orientation based on the tile the AI is moving towards
	Vec3 distance = targetTile.GetPos() - body->getPos();
	
	float d = sqrt(distance.x * distance.x + distance.y * distance.y);

	if (d > 2) targetOrientation = std::atan2(-distance.x, -distance.y);

	//If AI reaches tile then update the previous and current tile variables and re-calculate the closest tiles
	if (d < 0.01)
	{
	
		previousTile = currentTile;
		currentTile = targetTile;
		resetTileCheck = false;
	}

	//Work In Progress; Find the next tile the AI is going to move towards so that the orientation can be updated smoothly
	if (resetTileCheck == true)
	{

		for (int i = 0; i < closeTiles.size(); i++)

		{
			if (closeTiles.at(i).GetID() != currentTile.GetID())
			{
				if (closeTiles.at(i).GetID() != previousTile.GetID())
				{
					if (closeTiles.at(i).GetID() != targetTile.GetID())
					{
						if (closeTiles.at(i).TileStatus())
						{

							nextTile = closeTiles.at(i);
							break;
							
						}
					}
				}
			}

		}

	}
	float nextOrientation = 0;
	//Work In Progress; Update orientation based on the angle difference between the current tile and the next tile
	//if (d < 0.5)
	//{

	//	Vec3 newDistance = nextTile.GetPos() - body->getPos();

	//	nextOrientation = std::atan2(-newDistance.x, -newDistance.y) / M_PI;

	//	if (nextOrientation > targetOrientation && (nextOrientation - targetOrientation > 0.1))
	//	{
	//		targetOrientation += 0.1;
	//	}
	//	if (nextOrientation < targetOrientation && (targetOrientation - nextOrientation > 0.1))
	//	{
	//		targetOrientation -= 0.1;
	//	}
	//
	//}

	body->setOrientation(targetOrientation);
	
}

//Return the status of the closest tile
bool Character::CheckForClosestTile()
{
	
	return closeTiles.at(1).TileStatus();
	
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


