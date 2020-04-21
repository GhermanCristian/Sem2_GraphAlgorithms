#include <iostream>
#include "weightedGraph.h"

int main() {
	int sourceVertex;
	int destVertex;
	WeightedGraph currentGraph("graph5.txt");
	currentGraph.computeAPSP();

	while (1) {
		std::cout << "Insert source and destination vertex: ";
		std::cin >> sourceVertex >> destVertex;

		if (sourceVertex == -1) {
			break;
		}

		std::cout << currentGraph.getMinimumDistance(sourceVertex, destVertex) << "\n";
	}
	
	return 0;
}