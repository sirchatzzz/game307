#pragma once
#include "Steering/SteeringOutput.h"
#include "VMath.h"
#include "Character.h"

using namespace MATH;

class Arrive
{
private:

	float maxAccel;
	float maxSpeed;

	float targetRadius;
	float slowRadius;
	float timeToTarget = 0.1;


public:

	Arrive(float maxAccel_, float maxSpeed_, float targetRadius_, float slowRadius_, float timeToTarget_ = 0.1);
	SteeringOutput* getSteering(Vec3 target_, Character* character_);

	float GetSlowRadius() { return slowRadius; }
	float GetTargetRadius() { return targetRadius; }

};

