#include "weightedGraph.h"
#include <iostream>

WeightedGraph::WeightedGraph() : Graph() {
	cout << "Done with the weighted graph constructor\n";
}

int WeightedGraph::getEdgeCost(int srcVertex, int destVertex) {
	if (getEdge(srcVertex, destVertex, Graph::outEdges) == -1) {
		throw 1;
	}
	return costEdges[Edge(srcVertex, destVertex)];
}

void WeightedGraph::modifyEdgeCost(int srcVertex, int destVertex, int newCost) {
	if (getEdge(srcVertex, destVertex, Graph::outEdges) == -1) {
		throw 1;
	}
	costEdges[Edge(srcVertex, destVertex)] = newCost;
}

void WeightedGraph::addEdge(int srcVertex, int destVertex, int cost) {
	if (isEdge(srcVertex, destVertex) == true) {
		throw 1;
	}
	Graph::outEdges[srcVertex].push_back(AdjacentVertex(destVertex, cost));
	Graph::inEdges[destVertex].push_back(AdjacentVertex(srcVertex, cost));
	Edge newEdge(srcVertex, destVertex);
	costEdges[newEdge] = cost;
	nrEdges++;
}

void WeightedGraph::removeEdge(int srcVertex, int destVertex) {
	Graph::removeEdge(srcVertex, destVertex);
	costEdges.erase(Edge(srcVertex, destVertex));
}

void WeightedGraph::printGraph() {
	for (int i = 0; i < nrTotalVertices; i++) {
		if (isActiveVertex(i)) {
			for (auto it = Graph::outEdges[i].begin(); it != Graph::outEdges[i].end(); ++it) {
				cout << i << " " << it->index << " " << getEdgeCost(i, it->index) << "\n";
			}
		}
	}
}

void WeightedGraph::removeVertex(int vertex) {
	for (VectorIterator iter(outEdges[vertex]); iter.isValid(); ++iter) {
		costEdges.erase(Edge(vertex, (*iter).index));
	}
	Graph::removeVertex(vertex);
}

WeightedGraph::WeightedGraph(const WeightedGraph& originalGraph) {
	this->nrActiveVertices = originalGraph.nrActiveVertices;
	this->nrTotalVertices = originalGraph.nrTotalVertices;
	this->nrEdges = originalGraph.nrEdges;
	this->inEdges = originalGraph.inEdges;
	this->outEdges = originalGraph.outEdges;
	this->costEdges = originalGraph.costEdges;
}

WeightedGraph& WeightedGraph::operator=(const WeightedGraph& originalGraph){
	if (this != &originalGraph) {
		this->nrActiveVertices = originalGraph.nrActiveVertices;
		this->nrTotalVertices = originalGraph.nrTotalVertices;
		this->nrEdges = originalGraph.nrEdges;
		this->inEdges = originalGraph.inEdges;
		this->outEdges = originalGraph.outEdges;
		this->costEdges = originalGraph.costEdges;
	}
	return *this;
}

void WeightedGraph::clearGraph(){
	Graph::clearGraph();
	costEdges.clear();
}