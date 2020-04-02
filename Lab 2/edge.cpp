#include "edge.h"
using namespace std;

Edge::Edge(int srcVertex, int destVertex) {
	this->srcVertex = srcVertex;
	this->destVertex = destVertex;
}

bool Edge::operator == (const Edge& newEdge) const {
	return (this->srcVertex == newEdge.srcVertex && this->destVertex == newEdge.destVertex);
}