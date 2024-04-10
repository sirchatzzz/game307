#pragma once
#include "Arrive.h"
#include "Node.h"
#include "Path.h"
#include "Character.h"

class FollowAPath : public Arrive
{
public:

	FollowAPath() : Arrive(5,5,0,0.2f) {};
	~FollowAPath() {};

	SteeringOutput* getSteering(Path* path, Character* character);

};

