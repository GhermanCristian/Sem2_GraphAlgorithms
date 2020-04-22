#pragma once
#include <vector>
#include <unordered_map>
#include <fstream>
#include "edge.h"
#include "customHash.h"

const int NON_EXISTENT = 11111111;

class Graph {
	private:
		std::vector < int > topologicalOrder;
		std::vector < bool > visited;
		void DFSTopologicalSort(int srcVertex);
		void topologicalSort();

	protected:
		std::vector < std::vector <int> > inEdges;
		std::vector < std::vector <int> > outEdges;
		std::vector < int > minDistance;
		std::vector < int > walkCount;

	public:
		int numberOfEdges;
		int numberOfVertices;

		Graph();
		void resetGraph();
		void addVertex();
		void addEdge(int sourceVertex, int destVertex);
		bool isEdge(int sourceVertex, int destVertex);
		void loadGraphFromFile(const std::string& filePath);
		void determineMinDistanceAndWalks(int sourceVertex);
		int getMinDistance(int destVertex);
		int getWalksCount(int destVertex);
};