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
		int hamPathCost; // used in both methods

		std::unordered_map <Edge, int, CustomHashFunction> costEdges;
		std::vector < std::vector <int> > inEdges;
		std::vector < std::vector <int> > outEdges;

		std::vector<Edge> allEdges; // used in the sorted edges method
		std::vector<Edge> hamPathEdges; // used in the sorted edges method
		std::vector<int> visitCount; // used in the sorted edges method

		std::vector<int> hamPathVertices; // used in the nearest neighbour method
		std::vector<bool> visited; // used in the nearest neighbour method
		int originalVertex; // used in the nearest neighbour method

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
		/*
			Returns the cost of the edge from a to b (used in unoriented graphs)
			Input:
				- The 2 endpoints of the edge
				- The edge must exist
			Output:
				- The cost of the edge
		*/

		bool DFSNearestNeighbour(int sourceVertex, int cycleLength);
		/*
			Performs a DFS traversal, used in the nearest-neighbour algorithm
			Input:
				- The vertex we start from
				- The length of the cycle so far (or the current depth in the DFS tree)
			Output:
				- Returns true, if a cycle of length n (= the number of vertices) was found 
				(either at this vertex or in one of its successors)
				- Returns false, otherwise
		*/

		bool selectEdgesRec(int positionInEdgeList, int cycleLength);
		/*
			Performs a recursive, backtracking-like traversal of the list of sorted edges
			Input:
				- The current position in the sorted edge list
				- The number of edges that have been selected so far
			Output:
				- Returns true, if a cycle of length n (= the number of vertices) was found 
				- Returns false, otherwise
		*/

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
		/*
			Approximates the salesman problem by sorting the edges in increasing order of their cost
			and choosing them such that they don't form cycles of length < n (= number of vertices)
			Input:
				- None
			Output:
				- The vector which contains the edges in the cycle is filled
				- The cost of the cycle is computed
		*/

		void approximateTSPNearestNeighbour();
		/*
			Approximates the salesman problem by choosing, for each vertex, the closest one to it,
			such that they don't form cycles of length < n (= number of vertices)
			Input:
				- None
			Output:
				- The vector which contains the vertices in the cycle is filled
				- The cost of the cycle is computed
		*/

		int getHamPathCost();
		/*
			Returns the cost of the hamiltonian path
			Input:
				- Either approximateTSPSortingEdges or approximateTSPNearestNeighbour have to be called prior to this
		*/

		const std::vector<int>& getHamPathVertices();
		/*
			Returns the vector with the vertices from the hamiltonian path
			Input:
				- approximateTSPNearestNeighbour has to be called prior to this
		*/

		const std::vector<Edge>& getHamPathEdges();
		/*
			Returns the vector with the edges from the hamiltonian path
			Input:
				- approximateTSPSortingEdges has to be called prior to this
		*/

		~WeightedGraph();
		/*
			Destructor
			Input:
				- None
			Output:
				- The object is destroyed
		*/
};