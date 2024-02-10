#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "Steering/KinematicBody.h"


using namespace std;

class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;
	float speed;
	Vec3 target;
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


};

#endif

