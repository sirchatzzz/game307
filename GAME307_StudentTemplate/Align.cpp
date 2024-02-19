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

	//float rotation = targetOrientation_ - character_->getBody()->getOrientation();
	//rotation = mapToRange(rotation);
	//float rotationSize = abs(rotation);
	//if (rotationSize < targetRadius) return result;
	//
	//float currentRotation;

	//if (rotationSize > slowRadius) currentRotation = maxRotation;
	//else currentRotation = maxRotation * rotationSize / slowRadius;

	//currentRotation *= rotation / rotationSize;

	//result->angular = currentRotation - character_->getBody()->getRotation();
	//result->angular /= timeToTarget;

	//float angularAccel = abs(result->angular);
	//if (angularAccel > maxAngularAccel)
	//{

	//	result->angular /= angularAccel;
	//	result->angular *= maxAngularAccel;

	//}
	Vec3 distance = targetPos_ - character_->getBody()->getPos();
	result->angular = std::atan2(-distance.x, -distance.y);

	return result;

}
