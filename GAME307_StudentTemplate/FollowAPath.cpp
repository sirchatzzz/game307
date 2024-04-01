#include "FollowAPath.h"


SteeringOutput* FollowAPath::getSteering(Path* path, Character* character)
{
    Vec3 target_position;

    if (path->GetCurrentNode() == nullptr) return nullptr;

    target_position = path->GetCurrentNodePosition();

    std::cout << "\n" << VMath::distance(character->getBody()->getPos(), target_position) << ", " << GetSlowRadius();
    if(VMath::distance(character->getBody()->getPos(), target_position) <= GetSlowRadius())
    {

        // incremented for next steering request

        path->MoveToNextNode();
        if(path->GetCurrentNode() != NULL)
            target_position = path->GetCurrentNodePosition();
       
    }

    return Arrive::getSteering(target_position, character);

}
