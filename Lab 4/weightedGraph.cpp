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

void WeightedGraph::loadGraphFromFile(std::string filePath) {
	int sourceVertex, destVertex, edgeCost;

	std::ifstream in(filePath);
	in >> this->numberOfVertices >> this->numberOfEdges;
	this->resetGraph();
	for (int i = 0; i < this->numberOfEdges; i++) {
		in >> sourceVertex >> destVertex >> edgeCost;
		this->addEdge(sourceVertex, destVertex, edgeCost);
	}

	in.close();
}

WeightedGraph::~WeightedGraph(){
	;
}
