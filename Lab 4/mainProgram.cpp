#include <iostream>
#include "graph.h"
#include "weightedGraph.h"

void MSTKruskal() {
	WeightedGraph currentGraph(false); // weighted unoriented graph
	currentGraph.loadGraphFromFile("graph8_uno_w.txt");
	std::cout << "Cost: " << currentGraph.getMSTCostKruskal() << "\n";
	std::cout << "Edges:\n";
	std::vector <Edge> minimumSpanningTreeEdges = currentGraph.getMSTEdgesKruskal();
	for (auto currentEdge : minimumSpanningTreeEdges) {
		std::cout << currentEdge.srcVertex << " " << currentEdge.destVertex << "\n";
	}
}

void distinctPaths() {
	int sourceVertex;
	int destVertex;
	int distinctPathCount;
	Graph currentGraph(true); // unweighted oriented graph
	currentGraph.loadGraphFromFile("graph8_o_unw.txt");

	if (currentGraph.checkIfAcyclic() == false) {
		std::cout << "The graph is not acyclic\n";
	}
	else {
		std::cout << "Insert sourceVertex destVertex\n";
		std::cin >> sourceVertex >> destVertex;
		try {
			distinctPathCount = currentGraph.countDistinctPaths(sourceVertex, destVertex);
			std::cout << "Number of distinct paths: " << distinctPathCount << "\n";
		}
		catch (const std::exception& currentException) {
			std::cout << currentException.what() << "\n";
		}
	}
}

void distinctPathsLowestCost() {
	int sourceVertex;
	int destVertex;
	int distinctPathLowestCostCount;
	WeightedGraph currentGraph(true); // weighted oriented graph
	currentGraph.loadGraphFromFile("graph8_o_w.txt");

	if (currentGraph.checkIfAcyclic() == false) {
		std::cout << "The graph is not acyclic\n";
	}
	else {
		std::cout << "Insert sourceVertex destVertex\n";
		std::cin >> sourceVertex >> destVertex;
		try {
			distinctPathLowestCostCount = currentGraph.countDistinctPathsLowestCost(sourceVertex, destVertex);
			std::cout << "Number of distinct paths: " << distinctPathLowestCostCount << "\n";
		}
		catch (const std::exception& currentException) {
			std::cout << currentException.what() << "\n";
		}
	}
}

int main() {
	int command;

	while (true) {
		std::cout << "Insert command\n";
		std::cout << "0. Exit\n";
		std::cout << "1. Kruskal\n";
		std::cout << "2. Distinct paths\n";
		std::cout << "3. Distinct paths of lowest cost\n";
		std::cin >> command;

		if (command == 0) {
			std::cout << "Program has ended\n";
			return 0;
		}
		else if (command == 1) {
			MSTKruskal();
		}
		else if (command == 2) {
			distinctPaths();
		}
		else if (command == 3) {
			distinctPathsLowestCost();
		}

		std::cout << "\n";
	}
	return 0;
}