#pragma once
#include "DecisionTreeNode.h"
class Decision : public DecisionTreeNode
{
public:
	DecisionTreeNode* trueNode;
	DecisionTreeNode* falseNode;

	Decision();
	Decision(DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_) { trueNode = trueNode_; falseNode = falseNode_; }

	DecisionTreeNode* makeDecision() override;

	virtual bool testValue() = 0;

	virtual DecisionTreeNode* getBranch() = 0;

};

