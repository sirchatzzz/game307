#pragma once
#include <cmath>
#include "SteeringOutput.h"
#include "Character.h"
#include "Collider2D.h"


class Evade
{

private:

	float radius, maxAccel;

public:

	Evade(float radius_, float maxAccel_);

	SteeringOutput* getSteering(Character* character_, Vec3 collidedPosition_);



};

