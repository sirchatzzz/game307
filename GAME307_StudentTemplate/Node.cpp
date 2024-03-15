
#include "Node.h"
#include <stdio.h>

Node::Node()
{
    label = 0;
}

Node::Node(int i_)
{
    label = i_;
}

void Node::Print()
{
    printf("%i ", label);
    
}
