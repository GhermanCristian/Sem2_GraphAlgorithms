#pragma once
#include "edge.h"
#include "customHash.h"
#include <unordered_map>
#include <vector>

const int VERY_LARGE_COST = 999999999;

class WeightedGraph{
	private:
		int numberOfEdges;
		int numberOfVertices;
		int hamPathCost;

		std::unordered_map <Edge, int, CustomHashFunction> costEdges;
		std::vector < std::vector <int> > inEdges;
		std::vector < std::vector <int> > outEdges;

		std::vector<Edge> allEdges;
		std::vector<Edge> hamPathEdges; // used in the sorted edges method
		std::vector<int> visitCount; // used in the sorted edges method

		std::vector<int> hamPathVertices; // used in the nearest neighbour method
		std::vector<bool> visited; // used in the nearest neighbour method
		int originalVertex;

		void addVertex();
		/*
			Adds a new vertex to the graph (with the index being the largest so far)
			Input:
				- None
			Output:
				- The vertex is added to the graph
		*/

		void resetGraph();
		/*
			Resets the content of the graph
			Input:
				- None
			Output:
				- The edges of the graph are deleted
		*/

		int getEdgeCost(int a, int b);
		bool DFSNearestNeighbour(int sourceVertex, int cycleLength);
		bool selectEdgesRec(int positionInEdgeList, int cycleLength);
		
	public:
		WeightedGraph();
		/*
			Default constructor
			Input:
				- None
			Output:
				- The WeightedGraph object is built
		*/

		void addEdge(int sourceVertex, int destVertex, int edgeCost);
		/*
			Adds an edge from sourceVertex to destVertex, with a given cost
			Input:
				- The 2 ends of the edge and its cost
			Output:
				- The edge is added
		*/

		void loadGraphFromFile(std::string filePath);
		/*
			Loads a graph from a given file
			Input:
				- The path of the file we load from
			Output:
				- The graph contains the edges and vertices from the file
		*/

		void approximateTSPSortingEdges();
		void approximateTSPNearestNeighbour();

		int getHamPathCost();
		const std::vector<int>& getHamPathVertices();
		const std::vector<Edge>& getHamPathEdges();

		~WeightedGraph();
		/*
			Destructor
			Input:
				- None
			Output:
				- The object is destroyed
		*/

};