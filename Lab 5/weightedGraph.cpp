#include "weightedGraph.h"
#include "disjointSetForest.h"
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
	inEdges[sourceVertex].push_back(destVertex);
	outEdges[destVertex].push_back(sourceVertex);
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
	}

	in.close();
}

std::vector<Edge> WeightedGraph::approximateTSPSortingEdges(){
	std::vector<Edge> allEdges;
	std::vector<Edge> hamPathEdges;
	std::vector<int> remainingVertices;
	int* vertexDegree = new int[this->numberOfVertices];
	DisjointSetForest currentDSF(this->numberOfVertices);
	int root1, root2;

	for (int i = 0; i < this->numberOfVertices; i++) {
		vertexDegree[i] = 0;
	}
	for (auto currentEdge : costEdges) {
		allEdges.push_back(currentEdge.first);
	}
	std::sort(allEdges.begin(), allEdges.end(), [this](const Edge& a, const Edge& b) {return costEdges[a] < costEdges[b]; });
	
	this->hamPathCost = 0;
	for (auto currentEdge : allEdges) {
		root1 = currentDSF.findRoot(currentEdge.srcVertex);
		root2 = currentDSF.findRoot(currentEdge.destVertex);

		// the vertices are not from the same connected component
		if (root1 != root2) {
			currentDSF.uniteSets(root1, root2);
			hamPathEdges.push_back(currentEdge);
			vertexDegree[currentEdge.srcVertex]++;
			vertexDegree[currentEdge.destVertex]++;
			this->hamPathCost += costEdges[currentEdge];
		}
	}

	for (int i = 0; i < this->numberOfVertices; i++) {
		if (vertexDegree[i] == 1) {
			remainingVertices.push_back(i);
		}
	}

	hamPathEdges.push_back(Edge(remainingVertices[0], remainingVertices[1]));

	delete[] vertexDegree;
	return hamPathEdges;
}

void WeightedGraph::approximateTSPTakingLowestEdge()
{
}

int WeightedGraph::getHamPathCost(){
	return this->hamPathCost;
}

WeightedGraph::~WeightedGraph(){
	;
}
