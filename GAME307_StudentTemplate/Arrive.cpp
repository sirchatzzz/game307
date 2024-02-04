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
    //Create steering behaviour
    SteeringOutput* result;
    result = new SteeringOutput();

    //Find direction and distance between the target and AI
    Vec3 direction = target_ - character_->getBody()->getPos();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    //IF the distance is less than the target radius then return an empty steering behaviour to stop the AI
    if (distance < targetRadius) return result;

    //Create speed variables
    float currentSpeed;
    if (distance > slowRadius) currentSpeed = maxSpeed;
    else currentSpeed = maxSpeed * distance / slowRadius;
    
    //Create a velocity vector based on the direction and normalize it 
    Vec3 currentVelocity = direction;
    currentVelocity = VMath::normalize(currentVelocity);
    currentVelocity *= currentSpeed;

    //Set linear vector to be the calculated velocity subtracted by the AIs current velocity
    result->linear = currentVelocity - character_->getBody()->getVel();
    result->linear /= timeToTarget;

    //IF the length of the linear vector is greated than the max acceleration normalize the linear vector and multiple it by max acceleration
    if (sqrt(result->linear.x * result->linear.x + result->linear.y * result->linear.y + result->linear.z * result->linear.z) > maxAccel)
    {

        result->linear = VMath::normalize(result->linear);
        result->linear *= maxAccel;
    }
    
    //Set the angle to 0
    result->angular = 0;

    //Return the steering behaviour created in this function
    return result;


}
