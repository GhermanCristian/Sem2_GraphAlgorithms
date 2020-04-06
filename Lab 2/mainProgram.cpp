#include <iostream>
#include <fstream>
#include "weightedGraph.h"

void BFS() {
	WeightedGraph currentGraph(true); // weighted + oriented graph
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
}

void SCC() {
	WeightedGraph currentGraph(true); // unweighted + oriented graph
	currentGraph.loadGraphFromFile();
	currentGraph.computeSCC();

	std::cout << "Number of SCCs = " << currentGraph.getSCCCount() << "\n";
	std::vector < std::vector < int > > SCCList = currentGraph.getSCCList();
	for (auto SCC : SCCList) {
		for (auto vertex : SCC) {
			std::cout << vertex << " ";
		}
		std::cout << "\n\n";
	}
	std::cout << "\n";
}

void biconnected() {
	Graph currentGraph(false); // unweighted + unoriented
	//currentGraph.loadGraphFromFile();
	currentGraph.generateRandomGraph(1000, 4000);
	currentGraph.saveGraphToFile();
	currentGraph.computeBiComp();

	std::cout << "Number of biComps = " << currentGraph.getBiCompCount() << "\n";
	std::vector < std::vector <int> > biCompList = currentGraph.getBiCompList();
	for (auto biComp : biCompList) {
		for (auto vertex : biComp) {
			std::cout << vertex << " ";
		}
		std::cout << "\n\n";
	}
	std::cout << "\n";
}

int main() {
	int command;

	while (true) {
		std::cout << "0. Exit\n";
		std::cout << "1. BFS\n";
		std::cout << "2. Strongly-connected comp\n";
		std::cout << "3. Biconnected comp\n\n";
		std::cin >> command;

		if (command == 0) {
			std::cout << "Program has ended";
			break;
		}

		else if (command == 1) {
			BFS();
		}

		else if (command == 2) {
			SCC();
		}

		else if (command == 3) {
			biconnected();
		}
	}

	return 0;
}