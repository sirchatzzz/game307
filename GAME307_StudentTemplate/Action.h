#pragma once
#include "DecisionTreeNode.h"

class Action : public DecisionTreeNode
{

private:
	std::function<void(Vec3)> func;

public:

	Action();
	Action(std::function<void(Vec3)> func_) {
		func = func_; 

	}

	void takeAction() {
		func(Vec3());
	}

	DecisionTreeNode* makeDecision() override;


};

