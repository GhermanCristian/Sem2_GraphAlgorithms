#include <iostream>
#include "weightedGraph.h"

void minWalksCount() {
	int srcVertex, destVertex;
	WeightedGraph currentGraph;
	currentGraph.loadGraphFromFile("graph5.txt");

	std::cout << "Insert source and destination vertex: ";
	std::cin >> srcVertex >> destVertex;

	if (srcVertex == -1) {
		return;
	}

	try {
		currentGraph.dijkstraMinWalksCount(srcVertex);
		std::cout << "min dist: " << currentGraph.getMinDistance(destVertex) << "\n";
		std::cout << "nr of distinct walks: " << currentGraph.getMinWalksCount(destVertex) << "\n";
	}
	catch (std::exception& currentException) {
		std::cout << currentException.what() << "\n";
	}

	std::cout << "\n";
}

int main() {
	int command;

	while (true) {
		std::cout << "0. Exit\n";
		std::cout << "1. Min walks count\n";
		std::cout << "2. Distinct walks DAG\n\n";

		std::cin >> command;

		if (command == 0) {
			std::cout << "Program has ended\n";
			break;
		}

		if (command == 1) {
			minWalksCount();
		}

		else if (command == 2) {
			;
		}
	}
	
	return 0;
}