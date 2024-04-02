#include "Action.h"

Action::Action()
{
}

DecisionTreeNode* Action::makeDecision()
{

	takeAction();

	return this;
}
