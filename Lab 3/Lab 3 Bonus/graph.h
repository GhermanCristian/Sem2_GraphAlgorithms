#pragma once
#include <vector>
#include <unordered_map>
#include <fstream>
#include "edge.h"
#include "customHash.h"

const int NON_EXISTENT = 11111111;

class Graph {
	protected:
		std::vector < std::vector <int> > inEdges;
		std::vector < std::vector <int> > outEdges;

	public:
		int numberOfEdges;
		int numberOfVertices;

		Graph();
		void resetGraph();
		void addVertex();
		void addEdge(int sourceVertex, int destVertex);
		bool isEdge(int sourceVertex, int destVertex);
};