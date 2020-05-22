#include <iostream>
#include "weightedGraph.h"

void TSPApproximationSortedEdges() {
	WeightedGraph currentGraph;
	currentGraph.loadGraphFromFile("graph6.txt");

	std::vector<Edge> hamPathEdges = currentGraph.approximateTSPSortingEdges();
	std::cout<<"Hamiltonian path cost: "<< currentGraph.getHamPathCost() << "\n";
	for (auto currentEdge : hamPathEdges) {
		std::cout << currentEdge.srcVertex << " " << currentEdge.destVertex << "\n";
	}
}

void TSPApproximationTakeLowestEdge() {
	WeightedGraph currentGraph;
	currentGraph.loadGraphFromFile("graph6.txt");
	currentGraph.approximateTSPNearestNeighbour();

	std::vector<int> hamPathVertices = currentGraph.getHamPathVertices();
	std::cout << "Hamiltonian path cost: " << currentGraph.getHamPathCost() << "\n";
	for (int i = 0; i < hamPathVertices.size() - 1; i++) {
		std::cout << hamPathVertices[i] << " " << hamPathVertices[i + 1] << "\n";
	}
}

int main() {
	int command;

	while (1) {
		std::cout << "0. Exit\n";
		std::cout << "1. TSP approximation by sorting the edges\n";
		std::cout << "2. TSP approximation by taking the lowest cost edge\n";

		std::cin >> command;
		if (command == 0) {
			std::cout << "Program has ended\n";
			return 0;
		}
		if (command == 1) {
			TSPApproximationSortedEdges();
		}
		else if (command == 2) {
			TSPApproximationTakeLowestEdge();
		}

		std::cout << "\n";
	}

	return 0;
}