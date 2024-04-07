#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "Steering/KinematicBody.h"
#include "Collider2D.h"
#include "Tiles.h"
#include "Stats.h"
#include "Turret.h"
#include "Projectile.h"
#include "Path.h"
#include "Island.h"
#include "Node.h"

using namespace std;

enum AIState
{
	IDLE = 0,
	GOTOISLAND = 1,
	ATTACKTARGET = 2,
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
	Stats* enemyStats;

	//Turret object variable
	class Turret* turret;

	//Bullet vector
	class std::vector<Projectile> bullets;

	SDL_Surface** spriteImages;
	float animationCounter;

	float targetOrientation;

	//Variables to determine what and how fast an AI should execute tasks
	float aggroRadius;
	float attackRadius;
	float attackSpeed;

	Path islandPath;
	Path playerPath;

	bool patrolling;

	bool isDead;

	PlayerBody targetPlayer;
	Island targetIsland;

	AIState enemyState;

	std::vector<Island> islands;

	Node* currentNode = new Node(-1);
	Node* targetNode = new Node(-1);

	float attackTime = 0;
	float updatePlayerPathTime = 0;

public:

	/// <summary>
	/// A toggle so the scene knows if the AI is trying to calculate a new path
	/// </summary>
	bool calculateIslandPath = false;
	bool calculatePlayerPath = false;
	bool playerPathActive;

	bool calculateIsland = false;

public:
	Character()
	{
		body = NULL;
		scene = NULL;
	};

	~Character()
	{
		//if (body) delete body;
	};

	//Base functions for each class
	bool OnCreate(Scene* scene_);
	void OnDestroy() {};
	bool setImageWith(SDL_Surface** images_, int spriteIndex_);
	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f);

	//Setter for target
	void SetTargetPlayer(PlayerBody player_) { targetPlayer = player_; }
	PlayerBody GetTargetPlayer() { return targetPlayer; }

	//Check if character is near target
	bool checkIfNearTarget();

	//Getter for body 
	KinematicBody* getBody() { return body; }

	//Getter for collider 
	Collider2D GetCollider();

	//Getter for enemy stats
	Stats* GetEnemyStats() { return enemyStats; }

	void SetEnemyStats(Stats* enemyStats_) { enemyStats = enemyStats_; }
	
	//Getter for bullets
	std::vector<Projectile>* GetBullets() { return &bullets; }

	//Update the turret and bullets
	void UpdateTurret(float deltaTime_);
	void UpdateBullets(float deltaTime_);

	//Function to create and fire bullet
	void FireBullet();

	bool IsCharacterAtPos(Vec3 pos_);
	
	Path GetIslandPath() { return islandPath; }
	void SetIslandPath(Path path_) { islandPath = path_; }

	Path GetPlayerPath() { return playerPath; }
	void SetPlayerPath(Path path_) { playerPath = path_; }

	SDL_Surface** GetSpriteImages() { return spriteImages; }
	
	void EnemyDeath();

	bool IsDead() { return isDead; }

	void CalculateTargetIsland();
	void CalculateNextIsland();

	void SetIslands(std::vector<Island> islands_) { islands = islands_; }
	std::vector<Island> GetIslands() { return islands; }

	//Set Current Node that AI is on
	void SetCurrentNode(Node* node) { currentNode = node; }

	Node* GetCurrentNode() { return currentNode; }
	Node* GetTargetNode() { return targetNode; }

	void GoToIsland(Vec3 target_, SteeringOutput& steering_);
	void GoToPlayer(Vec3 target_, SteeringOutput& steering_);

	void AttackTarget(Vec3 target_);
	float CheckDistance(Vec3 target_) {

		Vec3 d = target_ - getBody()->getPos();
		return sqrt(d.x * d.x + d.y * d.y);
	}

};

#endif

