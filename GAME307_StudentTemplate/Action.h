#pragma once
#include "DecisionTreeNode.h"
#include <functional>


class Action : public DecisionTreeNode
{

private:

	std::function<void()> func;

public:

	Action();
	Action(std::function<void()> func_) { func = func_; }

	void takeAction() {
		func();
	}

	DecisionTreeNode* makeDecision() override;


};

