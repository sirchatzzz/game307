#pragma once
#include "Node.h"
#include "VMath.h"
#include <vector>

using namespace MATH;

class Path
{
private:
	Node* currentNode;
	std::vector<Node*> thePath;
	int totalTiles;
	int nodeIterator;

public:

	Path(std::vector<Node*> thePath_);
	Path() {};
	~Path();
	
	void MoveToNextNode();
	Vec3 GetCurrentNodePosition();
	Node* GetCurrentNode() {return currentNode;}
	bool IsPathEmpty();
	void SetPath(std::vector<Node*> path);
	std::vector<Node*> GetPath() { return thePath; }
};

