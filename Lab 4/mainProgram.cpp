#include <iostream>
#include "graph.h"
#include "weightedGraph.h"

int main() {
	WeightedGraph currentGraph(false); // weighted unoriented graph
	currentGraph.loadGraphFromFile("graph8_uno_w.txt");
	std::cout << "Cost: " << currentGraph.getMSTCostKruskal() << "\n";
	std::cout << "Edges:\n";
	std::vector <Edge> minimumSpanningTreeEdges = currentGraph.getMSTEdgesKruskal();
	for (auto currentEdge : minimumSpanningTreeEdges) {
		std::cout << currentEdge.srcVertex << " " << currentEdge.destVertex << "\n";
	}
	return 0;
}