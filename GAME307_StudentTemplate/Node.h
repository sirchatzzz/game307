#ifndef NODE_H
#define NODE_H
#include "VMath.h"

using namespace MATH;

class Node
{
private: 
	int label;
	Vec3 pos;

public:


	Node(int label_) : label{ label_ } {};

	int getLabel() { return label; }

	Vec3 GetPos() { 
		if (pos == NULL) 
			return Vec3(); 
		return pos; 
	}

	void SetLabel(int newLabel) { label = newLabel; }

	void SetPos(Vec3 pos_) { pos = pos_; }

	void Print();


};

#endif 


