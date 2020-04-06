#include "weightedGraph.h"
#include <iostream>

WeightedGraph::WeightedGraph() : Graph(){
	;
}

WeightedGraph::WeightedGraph(bool isOriented) : Graph(isOriented) {
	;
}

void WeightedGraph::addEdge(int sourceVertex, int destVertex, int edgeCost){
	Graph::addEdge(sourceVertex, destVertex);
	costEdges[Edge(sourceVertex, destVertex)] = edgeCost;
	if (this->isOriented == false) {
		costEdges[Edge(destVertex, sourceVertex)] = edgeCost;
	}
}

bool WeightedGraph::addRandomEdge(int nrVertices) {
	int srcVertex = rand() % nrVertices;
	int destVertex = rand() % nrVertices;

	if (srcVertex == destVertex and isOriented == false) {
		return false;
	}

	if (this->isEdge(srcVertex, destVertex) == false) {
		int edgeCost = rand() % nrVertices;
		this->addEdge(srcVertex, destVertex, edgeCost);
		return true;
	}

	return false;
}

void WeightedGraph::loadGraphFromFile() {
	int sourceVertex, destVertex, edgeCost;
	std::string currentFile;

	// we assume the input is valid
	if (this->isOriented) {
		currentFile = CURRENT_WEIGHTED_ORIENTED_GRAPH_FILE;
	}
	else {
		currentFile = CURRENT_WEIGHTED_UNORIENTED_GRAPH_FILE;
	}
	std::cout << "current file: " << currentFile << "\n";

	std::ifstream in(currentFile);
	in >> this->numberOfVertices >> this->numberOfEdges;
	this->resetGraph();
	for (int i = 0; i < this->numberOfEdges; i++) {
		in >> sourceVertex >> destVertex >> edgeCost;
		this->addEdge(sourceVertex, destVertex, edgeCost);
	}

	in.close();
}

void WeightedGraph::saveGraphToFile() {
	std::string currentFile;

	// we assume the input is valid
	if (this->isOriented) {
		currentFile = CURRENT_WEIGHTED_ORIENTED_GRAPH_FILE;
	}
	else {
		currentFile = CURRENT_WEIGHTED_UNORIENTED_GRAPH_FILE;
	}

	std::ofstream out(currentFile);
	out << this->numberOfVertices << " " << this->numberOfEdges << "\n";
	for (int srcVertex = 0; srcVertex < this->numberOfVertices; srcVertex++) {
		for (auto destVertex : outEdges[srcVertex]) {
			out << srcVertex << " " << destVertex << " " << costEdges[Edge(srcVertex, destVertex)] << "\n";
		}
	}
	out.close();
}

WeightedGraph::~WeightedGraph(){
	;
}
