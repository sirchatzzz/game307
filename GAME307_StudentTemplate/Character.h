#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "Steering/KinematicBody.h"
#include "Collider2D.h"
#include "Tiles.h"
#include "ShipStats.h"
#include "Turret.h"
#include "Projectile.h"

using namespace std;


class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;
	float speed;
	Vec3 target;
	Collider2D collider;
	Vec3 collidedTargetPosition;
	std::vector<Collider2D> islandColliders;
	
	//Near target variables
	bool near;

	//Enemy stats 
	ShipStats* enemyStats;

	//Turret object variable
	class Turret* turret;

	//Bullet vector
	class std::vector<Projectile> bullets;


	//Tile variables
	std::vector<Tiles> tiles;
	Tiles tile;
	Tiles targetTile;
	Tiles currentTile;
	Tiles previousTile;
	Tiles nextTile;
	std::vector<Tiles> closeTiles;
	bool resetTileCheck;

	float targetOrientation;

	//Variables to determine what and how fast an AI should execute tasks
	float aggroRadius;
	float attackRadius;
	float attackSpeed;

public:
	Character()
	{
		body = NULL;
		scene = NULL;
	};

	~Character()
	{
		if (body) delete body;
	};

	//Base functions for each class
	bool OnCreate(Scene* scene_);
	void OnDestroy() {};
	bool setImageWith(SDL_Surface* file);
	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f);

	//Setter for target
	void setTarget(Vec3 target_);

	//Check if character is near target
	bool checkIfNearTarget();

	//Getter for body 
	KinematicBody* getBody() { return body; }

	//Getter for collider 
	Collider2D GetCollider();

	//Island Avoidance Calculations
	void IslandAvoidance();
	void setIslandColliders(std::vector<Collider2D> islandColliders_) { islandColliders = islandColliders_; }

	//Getter for enemy stats
	ShipStats* GetEnemyStats() { return enemyStats; }

	//Setter for Tiles
	void SetTiles(std::vector<Tiles> tiles_) { tiles = tiles_; }

	//Tile Calculations
	void CalculateTiles();
	void PathfindTiles();
	bool CheckForClosestTile();
	
	//Getter for bullets
	std::vector<Projectile>* GetBullets() { return &bullets; }

	//Update the turret and bullets
	void UpdateTurret(float deltaTime_);
	void UpdateBullets(float deltaTime_);

	//Function to create and fire bullet
	void FireBullet();

	bool IsCharacterAtPos(Vec3 pos_);
};

#endif

