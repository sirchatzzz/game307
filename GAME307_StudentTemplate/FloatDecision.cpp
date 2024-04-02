#include "FloatDecision.h"

FloatDecision::FloatDecision()
{
}

bool FloatDecision::testValue()
{
    return false;
}

DecisionTreeNode* FloatDecision::getBranch()
{
    if (maxValue >= testValue() >= minValue) return trueNode;
        else return falseNode;
}
