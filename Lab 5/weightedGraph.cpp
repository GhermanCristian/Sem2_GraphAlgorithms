#include "weightedGraph.h"
#include <iostream>
#include <algorithm>
#include <fstream>

WeightedGraph::WeightedGraph(){
	this->numberOfEdges = 0;
	this->numberOfVertices = 0;
}

void WeightedGraph::addVertex() {
	std::vector <int> emptyVector;
	inEdges.push_back(emptyVector);
	outEdges.push_back(emptyVector);
}

void WeightedGraph::resetGraph() {
	inEdges.clear();
	outEdges.clear();

	for (int i = 0; i < this->numberOfVertices; i++) {
		addVertex();
	}
}

void WeightedGraph::addEdge(int sourceVertex, int destVertex, int edgeCost){
	inEdges[destVertex].push_back(sourceVertex);
	outEdges[sourceVertex].push_back(destVertex);
	costEdges[Edge(sourceVertex, destVertex)] = edgeCost;
}

void WeightedGraph::loadGraphFromFile(std::string filePath) {
	int sourceVertex, destVertex, edgeCost;

	std::ifstream in(filePath);
	in >> this->numberOfVertices >> this->numberOfEdges;
	this->resetGraph();
	for (int i = 0; i < this->numberOfEdges; i++) {
		in >> sourceVertex >> destVertex >> edgeCost;
		this->addEdge(sourceVertex, destVertex, edgeCost);
		this->addEdge(destVertex, sourceVertex, edgeCost);
	}

	in.close();
}

WeightedGraph::~WeightedGraph(){
	;
}
