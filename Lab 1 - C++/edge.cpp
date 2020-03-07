#include "edge.h"
using namespace std;

Edge::Edge(int srcVertex, int destVertex) {
	this->srcVertex = srcVertex;
	this->destVertex = destVertex;
}

bool Edge::operator == (const Edge& newEdge) const {
	if (this->srcVertex == newEdge.srcVertex)
		return this->destVertex < newEdge.destVertex;
	return this->srcVertex < newEdge.srcVertex;
}