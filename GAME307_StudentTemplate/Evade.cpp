#include "Evade.h"

Evade::Evade(float radius_, float maxAccel_)
{

    radius = radius_;
    maxAccel = maxAccel_;
}

SteeringOutput* Evade::getSteering(Character* character_, PlayerBody* target_)
{

    //Create steering behaviour
    SteeringOutput* result;
    result = new SteeringOutput();

    Vec3 relativePos = target_->getPos() - character_->getBody()->getPos();
    Vec3 relativeVel = target_->getVel() - character_->getBody()->getVel();
    float relativeSpeed = sqrt(relativeVel.x * relativeVel.x + relativeVel.y * relativeVel.y);
    float timeToCollision = VMath::dot(relativePos, relativeVel) / (relativeSpeed * relativeSpeed);
    
    float distance = sqrt(relativePos.x * relativePos.x + relativePos.y * relativePos.y);
    float minSeperation = distance - relativeSpeed * timeToCollision;
    
    if (minSeperation <= 0 || distance < (2 * radius)) relativePos = target_->getPos() - character_->getBody()->getPos();
    else relativePos = relativePos + relativeVel * timeToCollision;

    relativePos = VMath::normalize(relativePos);


    result->linear = relativePos * maxAccel;
    result->angular = 0;
    return result;








}
