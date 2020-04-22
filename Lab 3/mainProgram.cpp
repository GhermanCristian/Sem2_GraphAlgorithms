#include <iostream>
#include "weightedGraph.h"

int main() {
	int sourceVertex;
	int destVertex;
	WeightedGraph currentGraph("graph5.txt");
	if (currentGraph.computeAPSP() == true) {
		std::cout << "Cannot determine the min dist between 2 vertices\n";
	}
	else {
		while (1) {
			std::cout << "Insert source and destination vertex: ";
			std::cin >> sourceVertex >> destVertex;

			if (sourceVertex == -1) {
				break;
			}

			std::cout << currentGraph.getMinimumDistance(sourceVertex, destVertex) << "\n";
		}
	}
	
	return 0;
}