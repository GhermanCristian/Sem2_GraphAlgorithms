#include "node.h"

Node::Node(int index, int cost) {
	this->index = index;
	this->cost = cost;
}

bool Node::operator == (Node newNode) const {
	return this->index == newNode.index and this->cost == newNode.cost;
}