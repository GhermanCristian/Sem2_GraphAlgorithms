#include <iostream>
#include <fstream>
#include "weightedGraph.h"

int main() {
	WeightedGraph currentGraph;
	int sourceVertex, destVertex;

	currentGraph.loadGraphFromFile();
	std::cout << "Insert sourceVertex destVertex:\n";
	std::cin >> sourceVertex >> destVertex;

	try {
		currentGraph.BFS(sourceVertex, destVertex);
		std::cout << currentGraph.getDistanceToVertex(destVertex) << "\n";
		std::vector<int> pathToVertex = currentGraph.getPathToVertex(sourceVertex, destVertex);
		for (auto vertex : pathToVertex) {
			std::cout << vertex << " ";
		}
		std::cout << "\n\n";
	}
	catch (std::exception& programException) {
		std::cout << programException.what() << "\n\n";
	}

	currentGraph.computeSCC();
	std::cout << "Number of SCCs = " << currentGraph.getSCCCount() << "\n";
	std::vector < std::vector < int > > SCCList = currentGraph.getSCCList();
	for (auto SCC : SCCList) {
		for (auto vertex : SCC) {
			std::cout << vertex << " ";
		}
		std::cout << "\n";
	}

	return 0;
}