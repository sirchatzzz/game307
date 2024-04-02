#pragma once
#include "Decision.h"
class FloatDecision : public Decision
{
private:

	float minValue;
	float maxValue;
public:

	FloatDecision();

	FloatDecision(float minValue_, float maxValue_, DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_) {
		minValue = minValue_;
		maxValue = maxValue_;
		trueNode = trueNode_;
		falseNode = falseNode_;
	}

	bool testValue() override;
	
	DecisionTreeNode* getBranch() override;

};

