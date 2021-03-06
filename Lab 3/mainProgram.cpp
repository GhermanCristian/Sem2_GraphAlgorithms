#include <iostream>
#include "weightedGraph.h"

int main() {
	int sourceVertex;
	int destVertex;
	WeightedGraph currentGraph("graph5.txt");

	if (currentGraph.computeAPSP() == true) { // negative weight cycle
		std::cout << "Cannot determine the min dist between 2 vertices\n";
	}
	else {
		while (1) {
			std::cout << "Insert source and destination vertex: ";
			std::cin >> sourceVertex >> destVertex;

			if (sourceVertex == -1) {
				break;
			}

			try {
				std::cout << currentGraph.getMinimumDistance(sourceVertex, destVertex) << "\n";
				std::vector <int> minWalk = currentGraph.getMinimumWalk(sourceVertex, destVertex);
				std::cout << sourceVertex << " ";
				for (auto vertex : minWalk) {
					std::cout << vertex << " ";
				}
				std::cout << destVertex << "\n";
			}
			catch (const std::exception& currentException) {
				std::cout << currentException.what() << "\n";
			}
		}
	}
	
	return 0;
}