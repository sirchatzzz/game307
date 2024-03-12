#include "Align.h"

Align::Align()
{
}

Align::Align(float maxAngularAccel_, float maxRotation_, float targetRadius_, float slowRadius_, float timeToTarget_)
{

	//maxAngularAccel = maxAngularAccel_;
	//maxRotation = maxRotation_;
	//targetRadius = targetRadius_;
	//slowRadius = slowRadius_;
	//timeToTarget = timeToTarget_;

}

double mapToRange(double degrees) {

	double r = fmod(degrees, 360.0);

	if (r < -180.0)

		r += 360.0;

	if (r >= 180.0)

		r -= 360.0;

	return r;

}
SteeringOutput* Align::getSteering(Vec3 targetPos_, Character* character_)
{

	//Create steering behaviour
	SteeringOutput* result;
	result = new SteeringOutput();	

	Vec3 distance = targetPos_ - character_->getBody()->getPos();
	result->angular = std::atan2(-distance.x, -distance.y);

	return result;

}
