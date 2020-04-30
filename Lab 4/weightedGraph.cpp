#include "weightedGraph.h"
#include "disjointSetForest.h"
#include <iostream>
#include <algorithm>

WeightedGraph::WeightedGraph() : Graph(){
	;
}

WeightedGraph::WeightedGraph(bool isOriented) : Graph(isOriented) {
	;
}

void WeightedGraph::addEdge(int sourceVertex, int destVertex, int edgeCost){
	Graph::addEdge(sourceVertex, destVertex);
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

bool WeightedGraph::edgeCostCompareFunction(const Edge& a, const Edge& b){
	return costEdges[a] < costEdges[b];
}

int WeightedGraph::getEdgeCost(int a, int b)
{
	int edgeCost;
	try {
		edgeCost = this->costEdges[Edge(a, b)];
		return edgeCost;
	}
	catch(...) {
		try {
			edgeCost = this->costEdges[Edge(b, a)];
			return edgeCost;
		}
		catch (...) {
			return 0;
		}
	}
}

int WeightedGraph::getMSTCostKruskal(){
	DisjointSetForest currentDSF(this->numberOfVertices);
	std::vector <Edge> edges;
	int root1, root2;
	int totalCost = 0;

	minimumSpanningTreeEdges.clear();
	for (auto currentEdge : costEdges) {
		edges.push_back(currentEdge.first);
	}
	std::sort(edges.begin(), edges.end(), [this](const Edge& a, const Edge& b) {return costEdges[a] < costEdges[b]; });
	
	for (auto currentEdge : edges) {
		root1 = currentDSF.findRoot(currentEdge.srcVertex);
		root2 = currentDSF.findRoot(currentEdge.destVertex);
		
		// the vertices are not from the same connected component
		if (root1 != root2) {
			currentDSF.uniteSets(root1, root2);
			totalCost += costEdges[currentEdge];
			minimumSpanningTreeEdges.push_back(currentEdge);
		}
	}

	return totalCost;
}

const std::vector<Edge>& WeightedGraph::getMSTEdgesKruskal(){
	return this->minimumSpanningTreeEdges;
}

WeightedGraph::~WeightedGraph(){
	;
}
