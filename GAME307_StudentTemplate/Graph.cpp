#include "Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

bool Graph::OnCreate(std::vector<Node*> nodes_)
{
	// given a list of nodes, initialize a matrix of costs with 0.0
	int numNodes = nodes_.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		//populate the internal map
		if (i != nodes_[i]->getLabel())
		{
			std::cerr << "node with label 'i' not in the 'i' position for " << i << "\n";
			return false;
		}
		node[i] = nodes_[i];

		//set up connections
		cost[i].resize(numNodes);

		for (int j = 0; j < numNodes; j++)
		{
			cost[i][j] = 0.0f;
		}
	}

	return true;
}

int Graph::numNodes()
{
	return node.size();
}

void Graph::addWeightedConnection(Node* fromNode, Node* toNode, float weight)
{
	cost[fromNode->getLabel()][toNode->getLabel()] = weight;
}

std::vector<Node*> Graph::neighbours(Node* fromNode)
{
	std::vector<Node*> result = {};
	int from = fromNode->getLabel();
	for (int j = 0; j < numNodes(); j++)
	{
		if (cost[from][j] > 0.0f)
		{
			result.push_back(getNode(j));
		}
	}
	return result;
}

struct NodeAndPriority
{
	Node* node;
	float priority;

	bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs)
	{
		return lhs.priority > rhs.priority;
	}
};

std::vector<Node*> Graph::findPath(Node* startNode, Node* goalNode)
{
	// Declarations
	float new_cost;
	float priority;
	Node* currentNode = startNode;

	//Frontier
	std::priority_queue<NodeAndPriority, std::deque<NodeAndPriority>, NodeAndPriority > frontier;
	frontier.push(NodeAndPriority{ currentNode, 0.0f });
	
	//Track solution path 
	std::vector<int> came_from;
	// came_from[currentNode->getLabel()]
	came_from.resize(numNodes(), -1);

	// cost so far storage
	// use map, not vector, to allow detecting if a node has an entry
	int start = startNode->getLabel();
	int goal = goalNode->getLabel();
	std::map<int, float> cost_so_far;
	cost_so_far[start] = 0.0f;

	// TODO
	// loop through the frontier, while it is not empty


	while(!frontier.empty())
	{
		// get the top node, AND pop it off
		// if its the goal, then break out
		currentNode = frontier.top().node;
		frontier.pop();

		if (currentNode == goalNode)
		{
			break;
		}

		// for the neighbours of current node
		std::vector<Node*> ourNeighbours = neighbours(currentNode);

		for(auto nextDoor : ourNeighbours )
		{
			
			// calculate new cost
			// if you add heuristic() then you've got A*
			new_cost = cost_so_far[currentNode->getLabel()] + cost[currentNode->getLabel()][nextDoor->getLabel()];

			// if neighbour is not an index in cost_so_far OR new cost is lower

			if (cost_so_far.find(nextDoor->getLabel()) == cost_so_far.end() || new_cost < cost_so_far.at(nextDoor->getLabel()))
			{
				// found a better path, so update data structures

				//cost_so_far.at(nextDoor->getLabel()) = new_cost;
				//priority = new_cost; 
				
				cost_so_far[nextDoor->getLabel()] = new_cost;
				came_from[nextDoor->getLabel()] = currentNode->getLabel();
				frontier.push(NodeAndPriority{nextDoor, new_cost});
	
				
			}
		}
	}

	int lineCounter = 0;
	for (int i = 0; i < came_from.size(); i++)
	{

		if (came_from.at(i) != -1)
		{
			if (lineCounter++ > 24)
			{
				lineCounter = 0;
				std::cout << "\n";
			}
			std::cout << came_from[i] << " -> ";
			lineCounter++;
		}
	}
	
	std::cout << "\n\n";

	
	// Follow the breadcrumbs in came_from to produce path
	std::vector<Node*> path = {};
	// TODO
	currentNode = goalNode;
	while (currentNode != startNode)
	{
		path.push_back(currentNode);
		currentNode = getNode(came_from.at(currentNode->getLabel()));
	}

	std::reverse(path.begin(), path.end());

	for (int i = 0; i < path.size(); i++)
	{
		std::cout << path[i]->getLabel() << " -> ";
	}
	std::cout << std::endl;

	return path;
}

float Graph::GetWeightOfConnection(Node* fromNode, Node* toNode)
{	
	return	cost[fromNode->getLabel()][toNode->getLabel()];
}


