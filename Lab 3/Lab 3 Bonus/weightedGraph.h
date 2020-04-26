#pragma once
#include "graph.h"

class WeightedGraph : public Graph {
	private:
		std::unordered_map <Edge, int, CustomHashFunction> costEdges;

		// Dijkstra
		std::vector <int> minHeap; // this stores the actual vertices, in the given order
		std::vector <int> heapPosition; // this stores the position of each vertex in the heap, or -1 if it doesn't exist
		std::vector < int > minDistance;

		void upHeap(int vertexPosition);
		/*
			Updates a heap by trying to "lift" the vertex at a given position, while maintaining the heap properties
			Input:
				- The position of the vertex we want to "lift"
			Output:
				- The vertex is placed on the correct position, and the heap properties are still valid
		*/

		void insertInHeap(int vertex, int& heapLength);
		/*
			Inserts a new vertex to the heap
			Input:
				- The vertex we want to add
				- The length of the heap
			Output:
				- The vertex is added to the heap on the correct position
				- The length is increased by one
		*/

		void downHeap(int vertexPosition, int heapLength);
		/*
			Updates a heap by trying to "lower" a vertex at a given position, while maintaining the heap properties
			Input:
				- The position of the vertex we want to lower
				- The length of the heap
			Output:
				- The vertex is placed on the correct position, and the heap properties are still valid
		*/

		int extractHeapTop(int& heapLength);
		/*
			Extracts the top of the heap, and updates it to preserve the heap properties
			Input:
				- The length of the heap
			Output:
				- Returns the top of the heap
				- A new vertex is placed on the top of the heap
		*/

		void initialise();
		/*
			Initialises the vectors required for Dijkstra's algorithm
			Input:
				- None
			Output:
				- minDistance, walkCount, minHeap, heapPosition are all restored to their default states
		*/


	public:
		WeightedGraph();
		/*
			Constructor for the WeightedGraph class
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

		void loadGraphFromFile(const std::string& filePath);
		/*
			Loads a graph from a given file
			Input:
				- The path of the file we load from
			Output:
				- The graph contains the edges and vertices from the file
		*/

		void dijkstraMinWalkCount(int srcVertex);
		/*
			Performs Dijkstra's algorithm to determine the minimum distance
			and the number of minimal walks from srcVertex to all other vertices
			Input:
				- The vertex we start Dijkstra from
			Output:
				- The minDistance and walkCount vectors are filled
				- Throws an exception if the vertex doesn't exist
		*/

		int getMinDistance(int destVertex);
		/*
			Determines the minimum distance from the previous sourceVertex to destVertex
			Input:
				- The destination vertex
				- The minDistance has to be filled in advance
			Output:
				- Returns the minimum distance
				- Throws an exception if the vertex doesn't exist
		*/

		~WeightedGraph();
		/*
			Destructor for the WeightedGraph class
			Input:
				-
			Output:
				-
		*/

};