#ifndef NODE_H
#define NODE_H


class Node
{
private: 
	int label;

public:
	Node(int label_) : label{ label_ } {};

	int getLabel() { return label; };

	void Print();
};

#endif 


