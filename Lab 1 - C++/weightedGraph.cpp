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
	Graph::outEdges[srcVertex].push_back(Node(destVertex, cost));
	Graph::inEdges[destVertex].push_back(Node(srcVertex, cost));
	costEdges[Edge(srcVertex, destVertex)] = cost;
}

void WeightedGraph::removeEdge(int srcVertex, int destVertex) {
	Graph::removeEdge(srcVertex, destVertex);
	costEdges.erase(Edge(srcVertex, destVertex));
	cout << "rem edge from weighted\n";
}

void WeightedGraph::printGraph() {
	for (int i = 0; i < nrTotalVertices; i++) {
		if (isActiveVertex(i)) {
			cout << i << ": ";
			for (auto it = Graph::outEdges[i].begin(); it != Graph::outEdges[i].end(); ++it) {
				cout << it->index << " ";
			}
			cout << "\n";
		}
	}
}

void WeightedGraph::removeVertex(int vertex) {
	Graph::removeVertex(vertex);
	for (auto iter : costEdges) {
		if ((iter.first).srcVertex == vertex || (iter.first).destVertex == vertex) {
			costEdges.erase(Edge((iter.first).srcVertex, (iter.first).destVertex));
		}
	}
}