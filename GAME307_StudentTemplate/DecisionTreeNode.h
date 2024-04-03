#pragma once
#include <functional>
#include "VMATH.h"
#include "SteeringOutput.h"
#include "Path.h"
using namespace MATH;
class DecisionTreeNode abstract
{

public:

	virtual DecisionTreeNode* makeDecision() = 0;


};

