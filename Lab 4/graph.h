#pragma once
#include <vector>
#include <fstream>
const int NON_EXISTENT = -111111;

class Graph {
	protected:
		bool isOriented;
		std::vector < std::vector  <int> > inEdges;
		std::vector < std::vector  <int> > outEdges;
		std::vector<bool> inCurrentStack; 
		std::vector<bool> visited;
		std::vector<int> topologicalOrder;

		bool DFSCheckForCycles(int sourceVertex);
		void DFSTopologicalSort(int sourceVertex); // i know both can be done at the same time, but the code is clearer this way
		void topologicalSort();

	public:
		int numberOfEdges;
		int numberOfVertices;

		Graph();
		Graph(bool isOriented);
		void resetGraph();
		void addVertex();
		void addEdge(int sourceVertex, int destVertex);
		bool isEdge(int sourceVertex, int destVertex);
		bool checkIfAcyclic();
		int countDistinctPaths(int sourceVertex, int destVertex);
		virtual void loadGraphFromFile(std::string filePath);
};