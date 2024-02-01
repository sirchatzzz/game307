#include "Arrive.h"

Arrive::Arrive(float maxAccel_, float maxSpeed_, float targetRadius_, float slowRadius_, float timeToTarget_)
{

    maxAccel = maxAccel_;
    maxSpeed = maxSpeed_;
    targetRadius = targetRadius_;
    slowRadius = slowRadius_;
    timeToTarget = timeToTarget_;

}

SteeringOutput* Arrive::getSteering(Vec3 target_, Character* character_)
{
    SteeringOutput* result;
    result = new SteeringOutput();

    Vec3 direction = target_ - character_->getBody()->getPos();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

    if (distance < targetRadius) return result;

    float currentSpeed;
    if (distance > slowRadius) currentSpeed = maxSpeed;
    else currentSpeed = maxSpeed * distance / slowRadius;
    
    Vec3 currentVelocity = direction;
    currentVelocity = VMath::normalize(currentVelocity);
    currentVelocity *= currentSpeed;


    result->linear = currentVelocity - character_->getBody()->getVel();
    result->linear /= timeToTarget;

    if (sqrt(result->linear.x * result->linear.x + result->linear.y * result->linear.y + result->linear.z * result->linear.z) > maxAccel)
    {

        result->linear = VMath::normalize(result->linear);
        result->linear *= maxAccel;
    }
    
    result->angular;

    return result;


}
