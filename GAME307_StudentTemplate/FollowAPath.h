#pragma once
#include "Arrive.h"
#include "Node.h"
#include "Path.h"
#include "Character.h"

class FollowAPath : public Arrive
{
public:

	FollowAPath() : Arrive(4,4,0,0.75f) {};
	~FollowAPath() {};

	SteeringOutput* getSteering(Path* path, Character* character);

};

