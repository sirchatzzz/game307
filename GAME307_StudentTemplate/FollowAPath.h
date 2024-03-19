#pragma once
#include "Arrive.h"
#include "Node.h"

class FollowAPath : public Arrive
{
public:

	SteeringOutput* getSteering(Vec3 path);

};

