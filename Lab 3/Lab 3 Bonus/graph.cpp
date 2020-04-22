#include "graph.h"
#include <iostream>
#include <algorithm>

void Graph::DFSTopologicalSort(int srcVertex){
	this->visited[srcVertex] = true;

	for (auto vertex : outEdges[srcVertex]) {
		if (this->visited[vertex] == false) {
			DFSTopologicalSort(vertex);
		}
	}

	this->topologicalOrder.push_back(srcVertex);
}

void Graph::topologicalSort(){
	this->visited.clear();
	for (int i = 0; i < this->numberOfVertices; i++) {
		this->visited.push_back(false);
	}

	for (int vertex = 0; vertex < this->numberOfVertices; vertex++) {
		if (this->visited[vertex] == false) {
			DFSTopologicalSort(vertex);
		}	
	}

	std::reverse(this->topologicalOrder.begin(), this->topologicalOrder.end());
}

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
	if (isEdge(sourceVertex, destVertex) == true) {
		return;
	}

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

void Graph::loadGraphFromFile(const std::string& filePath){
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

void Graph::determineMinDistanceAndWalks(int sourceVertex){
	topologicalSort();

	this->walkCount.clear();
	for (int i = 0; i < this->numberOfVertices; i++) {
		this->walkCount.push_back(0);
	}
	this->walkCount[sourceVertex] = 1;

	for (auto vertex : this->topologicalOrder) {
		for (auto neighbour : outEdges[vertex]) {
			walkCount[neighbour] += walkCount[vertex];
		}
	}
}

int Graph::getMinDistance(int destVertex) {
	if (destVertex < 0 or destVertex >= this->numberOfVertices) {
		throw std::exception("Invalid vertex");
	}
	return minDistance[destVertex];
}

int Graph::getWalksCount(int destVertex) {
	if (destVertex < 0 or destVertex >= this->numberOfVertices) {
		throw std::exception("Invalid vertex");
	}
	return walkCount[destVertex];
}

