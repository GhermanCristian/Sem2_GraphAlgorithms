#include "adjacentVertex.h"

AdjacentVertex::AdjacentVertex(int index, int cost) {
	this->index = index;
	this->cost = cost;
}

bool AdjacentVertex::operator == (AdjacentVertex newNode) const {
	return this->index == newNode.index and this->cost == newNode.cost;
}