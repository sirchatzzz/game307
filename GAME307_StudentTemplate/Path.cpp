#include "Path.h"

Path::Path(std::vector<Node*> thePath_) : currentNode(nullptr), thePath(thePath_), totalTiles(0), nodeIterator(0)
{
	nodeIterator = 0;
	currentNode = thePath[nodeIterator];
	totalTiles = thePath.size()-1;


}

Path::~Path()
{
	delete currentNode;
	
}

void Path::MoveToNextNode()
{
	if (totalTiles > 0)
	{
		nodeIterator += 1;
		currentNode = thePath[nodeIterator];
		totalTiles--;
	}
	else
	{
		currentNode = nullptr;
	}

}

Vec3 Path::GetCurrentNodePosition()
{
	return currentNode->GetPos();
}
