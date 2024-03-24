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
#include "Path.h"

using namespace std;

enum AIState
{
	IDLE = 0,
	GOTOISLAND = 1,
	ATTACKPLAYER = 2,
	CHASEPLAYER = 3,
};


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

	Path characterPath;
	Path currentPath;
	bool patrolling;
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

	//Getter for enemy stats
	ShipStats* GetEnemyStats() { return enemyStats; }
	
	//Getter for bullets
	std::vector<Projectile>* GetBullets() { return &bullets; }

	//Update the turret and bullets
	void UpdateTurret(float deltaTime_);
	void UpdateBullets(float deltaTime_);

	//Function to create and fire bullet
	void FireBullet();

	bool IsCharacterAtPos(Vec3 pos_);

	Path GetCharacterPath() { return characterPath; }
	void SetCharacterPath(Path path_);
	
	Path GetCurrentPath() { return currentPath; }
	void SetCurrentPath(Path path_) { currentPath = path_; }
};

#endif

