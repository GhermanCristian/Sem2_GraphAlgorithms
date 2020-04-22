#include "edge.h"
using namespace std;

Edge::Edge(int srcVertex, int destVertex) {
	this->srcVertex = srcVertex;
	this->destVertex = destVertex;
}

bool Edge::operator == (const Edge& newEdge) const {
	return (this->srcVertex == newEdge.srcVertex and this->destVertex == newEdge.destVertex);
}

bool Edge::operator != (const Edge& newEdge) const {
	return (this->srcVertex != newEdge.srcVertex or this->destVertex != newEdge.destVertex);
}