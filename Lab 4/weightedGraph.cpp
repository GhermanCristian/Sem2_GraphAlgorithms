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

int WeightedGraph::countDistinctPathsLowestCost(int sourceVertex, int destVertex){
	if (destVertex < 0 or destVertex >= this->numberOfVertices or sourceVertex < 0 or sourceVertex >= this->numberOfVertices) {
		throw std::exception("Invalid vertex");
	}

	std::vector<int> distinctPaths; // number of paths from the source vertex to the vertex 'i'
	std::vector<int> lowestCost; // lowest cost of the path from the source vertex to the vertex 'i'
	int positionInSortedList = 0; // of the source vertex; it has a default value so that VS won't complain
	int currentVertex;

	for (int i = 0; i < this->numberOfVertices; i++) {
		distinctPaths.push_back(0);
		lowestCost.push_back(VERY_LARGE_COST);
	}
	distinctPaths[sourceVertex] = 1;
	lowestCost[sourceVertex] = 0;
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
			int edgeCost = costEdges[Edge(currentVertex, neighbour)];

			if (lowestCost[neighbour] > lowestCost[currentVertex] + edgeCost) {
				lowestCost[neighbour] = lowestCost[currentVertex] + edgeCost;
				distinctPaths[neighbour] = distinctPaths[currentVertex];
			}
			else if (lowestCost[neighbour] == lowestCost[currentVertex] + edgeCost) {
				distinctPaths[neighbour] += distinctPaths[currentVertex];
			}
		}
	}

	return distinctPaths[destVertex];
}

WeightedGraph::~WeightedGraph(){
	;
}
