#include "Evade.h"

Evade::Evade(float radius_, float maxAccel_)
{

    radius = radius_;
    maxAccel = maxAccel_;
}

SteeringOutput* Evade::getSteering(Character* character_, Vec3 collidedPosition_)
{

    //Create steering behaviour
    SteeringOutput* result;
    result = new SteeringOutput();

    Vec3 relativePos = collidedPosition_ - (character_->getBody()->getPos() * 1000);

    result->linear = VMath::normalize(relativePos) * maxAccel;
    result->angular = 0;
    return result;

}
