#pragma once
#include <vector>
#include <unordered_map>
#include <fstream>
#include "edge.h"
#include "customHash.h"

#define GRAPH_1K_UNWEIGHTED_ORIENTED "graph1k_unw.txt"
#define GRAPH_1K_UNWEIGHTED_UNORIENTED "graph1k_unw_uno.txt"

#define CURRENT_ORIENTED_GRAPH_FILE GRAPH_1K_UNWEIGHTED_ORIENTED
#define CURRENT_UNORIENTED_GRAPH_FILE GRAPH_1K_UNWEIGHTED_UNORIENTED

const int NON_EXISTENT = -111111;

class Graph {
	protected:
		bool isOriented;
		std::vector < std::vector  <int> > inEdges;
		std::vector < std::vector  <int> > outEdges;

		// BFS
		std::unordered_map <int, int> parent;
		std::unordered_map <int, int> distanceFromSource;

		// SCC
		int globalIndex;
		std::vector <int> inStack;
		std::vector <int> validNodeStack;
		std::vector <int> depth;
		std::vector <int> lowLink;
		std::vector < std::vector <int> > SCCList;
		void pushToStack(int newVertexIndex);
		void popFromStack();
		void tarjanDFS(int srcVertex);
		std::vector <int> newSCC(int SCCRoot);

	public:
		int numberOfEdges;
		int numberOfVertices;

		Graph();
		Graph(bool isOriented);
		void resetGraph();
		void addVertex();
		void addEdge(int sourceVertex, int destVertex);
		bool isEdge(int sourceVertex, int destVertex);
		virtual bool addRandomEdge(int nrVertices);
		void generateRandomGraph(int nrVertices, int nrEdges);
		void loadGraphFromFile();
		void saveGraphToFile();

		// BFS
		void BFS(int srcVertex, int destVertex);
		int getDistanceToVertex(int destVertex);
		std::vector <int> getPathToVertex(int srcVertex, int destVertex);

		// SCC
		void computeSCC();
		int getSCCCount();
		std::vector < std::vector <int> > getSCCList();
};