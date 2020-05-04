#pragma once
#include "graph.h"
#include "edge.h"
#include "customHash.h"
#include <unordered_map>

const int VERY_LARGE_COST = 999999999;

class WeightedGraph : public Graph {
	private:
		std::unordered_map <Edge, int, CustomHashFunction> costEdges;
		std::vector <Edge> minimumSpanningTreeEdges;
		
	public:
		WeightedGraph();
		/*
			Default constructor
			Input:
				- None
			Output:
				- The WeightedGraph object is built
		*/

		WeightedGraph(bool isOriented);
		/*
			Constructor
			Input:
				- Whether the graph is oriented or not
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

		virtual void loadGraphFromFile(std::string filePath);
		/*
			Loads a graph from a given file
			Input:
				- The path of the file we load from
			Output:
				- The graph contains the edges and vertices from the file
		*/

		int getMSTCostKruskal();
		/*
			Performs Kruskal's algorithm to determine a MST and its cost
			Input:
				- A DisjointSetForest, with each vertex representing a disjoint set
				- A list of the edges in the graph, which will be sorted
			Output:
				- Fills a list of the edges which form the MST 
				- Returns the cost of the MST
		*/

		const std::vector <Edge>& getMSTEdgesKruskal();
		/*
			Returns the list of edges which form the MST
			Input:
				- The function getMSTCostKruskal has to have been called prior to this (to fill the list)
			Output:
				- Returns the list
		*/

		int countDistinctPathsLowestCost(int sourceVertex, int destVertex);
		/*
			Counts the number of distinct paths from the sourceVertex to the destVertex, which have a minimum cost
			Input:
				- The two vertices
			Output:
				- Throws exception if the vertices are invalid
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