#include "weightedGraph.h"

WeightedGraph::WeightedGraph() : Graph(){
	;
}

void WeightedGraph::addEdge(int sourceVertex, int destVertex, int edgeCost){
	Graph::addEdge(sourceVertex, destVertex);
	costEdges[Edge(sourceVertex, destVertex)] = edgeCost;
}

void WeightedGraph::generateRandomGraph(int nrVertices, int nrEdges) {
	if (nrVertices * nrVertices < nrEdges) {
		return;
	}

	this->numberOfVertices = nrVertices;
	this->numberOfEdges = nrEdges;
	this->resetGraph();

	int srcVertex, destVertex, edgeCost;
	int nrExistingEdges = 0;

	while (nrExistingEdges < nrEdges) {
		srcVertex = rand() % nrVertices;
		destVertex = rand() % nrVertices;
		if (this->isEdge(srcVertex, destVertex) == false) {
			edgeCost = rand() % (2 * nrVertices);
			this->addEdge(srcVertex, destVertex, edgeCost);
			nrExistingEdges++;
		}
	}
}

void WeightedGraph::loadGraphFromFile() {
	int sourceVertex, destVertex, edgeCost;

	// we assume the input is valid
	ifstream in(CURRENT_GRAPH_FILE);
	in >> this->numberOfVertices >> this->numberOfEdges;
	this->resetGraph();
	for (int i = 0; i < this->numberOfEdges; i++) {
		in >> sourceVertex >> destVertex >> edgeCost;
		this->addEdge(sourceVertex, destVertex, edgeCost);
	}

	in.close();
}

void WeightedGraph::saveGraphToFile() {
	ofstream out(CURRENT_GRAPH_FILE);
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
