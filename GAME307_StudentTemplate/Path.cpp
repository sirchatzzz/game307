#include "Path.h"

Path::Path(std::vector<Node*> thePath_) : currentNode(nullptr), thePath(thePath_), totalTiles(0), nodeIterator(0)
{
	nodeIterator = 0;
	if (!thePath.empty()) currentNode = thePath[nodeIterator];
	totalTiles = thePath.size()-1;

}

Path::~Path()
{
	
}

void Path::MoveToNextNode()
{
	if (totalTiles > 0)
	{
		nodeIterator += 1;
		if (!thePath.empty()) currentNode = thePath[nodeIterator];
		totalTiles--;
	}
	else
	{
		currentNode = nullptr;
	}

}

Vec3 Path::GetCurrentNodePosition()
{	
	if (currentNode->GetPos().x != NULL)
	{
		return currentNode->GetPos();
	}
	
}

bool Path::IsPathEmpty()
{
	if (thePath.size() < 1)
		return true;

	return false;
}

void Path::SetPath(std::vector<Node*> path)
{
	if (!path.empty())
	{
		nodeIterator = 0;
		thePath = path;
		totalTiles = thePath.size() - 1;
		currentNode = path[nodeIterator];
	}
	
}


