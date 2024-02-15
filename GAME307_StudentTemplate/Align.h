#pragma once
#include <cmath>
#include "SteeringOutput.h"
#include <VMath.h>
#include "Character.h"
using namespace MATH;


class Align
{
	
private:


	float maxAngularAccel;
	float maxRotation;
	float targetRadius;
	float slowRadius;
	float timeToTarget = 0.1;


public: 

	Align(float maxAngularAccel_, float maxRotation_, float targetRadius_, float slowRadius_, float timeToTarget_ = 0.1);

	float getSteering(float targetOrientation_, Character* character_);


};

