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

bool Graph::DFSCheckForCycles(int sourceVertex) {
	bool callResult = false;

	visited[sourceVertex] = true;
	inCurrentStack[sourceVertex] = true;

	for (auto neighbour : outEdges[sourceVertex]) {
		if (visited[neighbour] == false) {
			if (inCurrentStack[neighbour] == true) {
				return true; // it has cycles
			}
			callResult = DFSCheckForCycles(neighbour);
			if (callResult == true) {
				return true; // we "propell" up the DFS tree the message that there are cycles
			}
		}
	}

	inCurrentStack[sourceVertex] = false;
	return callResult;
}

bool Graph::checkIfAcyclic() {
	bool hasCycles;

	inCurrentStack.clear();
	visited.clear();
	for (int i = 0; i < this->numberOfVertices; i++) {
		inCurrentStack.push_back(false);
		visited.push_back(false);
	}

	for (int i = 0; i < this->numberOfVertices; i++) {
		if (visited[i] == false) {
			hasCycles = DFSCheckForCycles(i);
			if (hasCycles == true) {
				return false;
			}
		}
	}

	return true;
}

void Graph::DFSTopologicalSort(int sourceVertex){
	this->visited[sourceVertex] = true;

	for (auto vertex : outEdges[sourceVertex]) {
		if (this->visited[vertex] == false) {
			DFSTopologicalSort(vertex);
		}
	}

	this->topologicalOrder.push_back(sourceVertex);
}

void Graph::topologicalSort(){
	this->visited.clear();
	this->topologicalOrder.clear();
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

int Graph::countDistinctPaths(int sourceVertex, int destVertex){
	if (destVertex < 0 or destVertex >= this->numberOfVertices or sourceVertex < 0 or sourceVertex >= this->numberOfVertices) {
		throw std::exception("Invalid vertex");
	}

	std::vector<int> distinctPaths;
	int positionInSortedList = 0; // of the source vertex; it has a default value so that VS won't complain
	int currentVertex;

	for (int i = 0; i < this->numberOfVertices; i++) {
		distinctPaths.push_back(0);
	}
	distinctPaths[sourceVertex] = 1;
	topologicalSort();

	// find the position of the source vertex in the topologically sorted vector, so that we can start directly from
	// there (otherwise, the number of paths to the source vertex will not remain 1, which will have a domino effect)
	for (int i = 0; i < this->numberOfVertices; i++) {
		if (topologicalOrder[i] == sourceVertex) {
			positionInSortedList = i;
			break;
		}
	}

	for (int i = positionInSortedList; i < this->numberOfVertices; i++) {
		currentVertex = topologicalOrder[i];
		for (auto neighbour : outEdges[currentVertex]) {
			distinctPaths[neighbour] += distinctPaths[currentVertex];
		}
	}

	return distinctPaths[destVertex];
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

