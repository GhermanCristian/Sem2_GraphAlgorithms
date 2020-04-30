#include "graph.h"
#include <queue>
#include <iostream>

Graph::Graph() {
	this->numberOfEdges = 0;
	this->numberOfVertices = 0;
	this->isOriented = false;
}

Graph::Graph(bool isOriented) {
	this->numberOfEdges = 0;
	this->numberOfVertices = 0;
	this->isOriented = isOriented;
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
	if (this->isOriented == false) {
		inEdges[sourceVertex].push_back(destVertex);
		outEdges[destVertex].push_back(sourceVertex);
	}
}

bool Graph::isEdge(int sourceVertex, int destVertex){
	for (auto iter : inEdges[destVertex]) {
		if (iter == sourceVertex) {
			return true;
		}
	}

	return false;
}

void Graph::loadGraphFromFile(std::string filePath) {
	int sourceVertex, destVertex;

	std::ifstream in(filePath);
	in >> this->numberOfVertices >> this->numberOfEdges;
	this->resetGraph();
	for (int i = 0; i < this->numberOfEdges; i++) {
		in >> sourceVertex >> destVertex;
		this->addEdge(sourceVertex, destVertex);
	}

	in.close();
}

