#pragma once
#include "Decision.h"
class FloatDecision : public Decision
{
private:

	float minValue;
	float maxValue;

	std::function<float(Vec3)> func;

public:

	FloatDecision();

	FloatDecision(float minValue_, float maxValue_, DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_, std::function<float(Vec3)> func_) {
		minValue = minValue_;
		maxValue = maxValue_;
		trueNode = trueNode_;
		falseNode = falseNode_;
		func = func_;
	}

	void checkDistance(float &a) {
		a = func(Vec3());
	}


	float testValue() override;
	
	DecisionTreeNode* getBranch() override;

};

