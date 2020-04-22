#include "graph.h"
#include <queue>
#include <iostream>

Graph::Graph() {
	this->numberOfEdges = 0;
	this->numberOfVertices = 0;
}

void Graph::resetGraph() {
	inEdges.clear();
	outEdges.clear();

	for (int i = 0; i < this->numberOfVertices; i++) {
		addVertex();
	}
}

void Graph::addVertex() {
	std::vector <int> emptyVector;
	inEdges.push_back(emptyVector);
	outEdges.push_back(emptyVector);
}

void Graph::addEdge(int sourceVertex, int destVertex){
	inEdges[destVertex].push_back(sourceVertex);
	outEdges[sourceVertex].push_back(destVertex);
}

bool Graph::isEdge(int sourceVertex, int destVertex){
	for (auto iter : inEdges[destVertex]) {
		if (iter == sourceVertex) {
			return true;
		}
	}

	return false;
}

