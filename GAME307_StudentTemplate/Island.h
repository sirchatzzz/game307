#ifndef ISLAND_H
#define ISLAND_H

#include <vector>

#include "Scene.h"
#include "Steering/KinematicBody.h"
#include "Collider2D.h"

using namespace std;

class Island
{
private:
	class Body* body;
	class Scene* scene;

	Collider2D collider;

	//Enemy stats 
	Stats* stats;

public:
	Island()
	{
		body = NULL;
		scene = NULL;
	};

	~Island()
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

	//Getter for body 
	Body* getBody() { return body; }

	//Getter for collider 
	Collider2D GetCollider();

	//Getter for enemy stats
	Stats* GetStats() { return stats; }

};

#endif
