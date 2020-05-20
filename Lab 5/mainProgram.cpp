#include <iostream>
#include "weightedGraph.h"

void TSPApproximationSortedEdges() {
	WeightedGraph currentGraph;
	currentGraph.loadGraphFromFile("graph6.txt");

}

void TSPApproximationTakeLowestEdge() {
	WeightedGraph currentGraph;
	currentGraph.loadGraphFromFile("graph6.txt");

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