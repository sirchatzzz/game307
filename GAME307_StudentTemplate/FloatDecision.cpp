#include "FloatDecision.h"

FloatDecision::FloatDecision()
{
}

float FloatDecision::testValue()
{
    float a;
    checkDistance(a);
    return a;
}

DecisionTreeNode* FloatDecision::getBranch()
{
    if (maxValue > testValue() > minValue) return trueNode;
        else return falseNode;
}
