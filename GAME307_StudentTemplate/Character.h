#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "Steering/KinematicBody.h"
#include "Collider2D.h"

using namespace std;

class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;
	float speed;
	PlayerBody* target;
	Collider2D collider;
	Vec3 collidedTargetPosition;
	std::vector<Collider2D> islandColliders;
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
	void setTarget(PlayerBody* target_);

	//void steerTo(Vec3 target_, float speed_, SteeringOutput* steering_);
	bool checkIfNearTarget();
	KinematicBody* getBody() { return body; }

	Collider2D GetCollider();

	bool IslandAvoidance();
	void setIslandColliders(std::vector<Collider2D> islandColliders_) { islandColliders = islandColliders_; }
};

#endif

