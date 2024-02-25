#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "Steering/KinematicBody.h"
#include "Collider2D.h"
#include "Tiles.h"
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
	Vec3 nearTargetAccel;
	bool near;

	std::vector<Tiles> tiles;

	Tiles tile;
	Tiles targetTile;
	Tiles currentTile;
	Tiles previousTile;
	Tiles nextTile;
	std::vector<Tiles> closeTiles;
	

	bool resetTileCheck;
	float targetOrientation;

	float aggroRadius;


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

	bool OnCreate(Scene* scene_);
	void OnDestroy() {};
	bool setTextureWith(string file);
	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f);
	void setTarget(Vec3 target_);

	//void steerTo(Vec3 target_, float speed_, SteeringOutput* steering_);
	bool checkIfNearTarget();
	KinematicBody* getBody() { return body; }

	Collider2D GetCollider();

	void IslandAvoidance();
	void setIslandColliders(std::vector<Collider2D> islandColliders_) { islandColliders = islandColliders_; }
	void SetTiles(std::vector<Tiles> tiles_) { tiles = tiles_; }

	void CalculateTiles();
	void PathfindTiles();
	bool CheckForClosestTile();
};

#endif

