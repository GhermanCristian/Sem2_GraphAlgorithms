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
		std::vector<int> topologicalOrder; // will contain the vertices of the graph sorted in topological order

		bool DFSCheckForCycles(int sourceVertex);
		/*
			Performs a DFS starting from a sourceVertex; it checks whether the sub-graph has cycles
			Input:
				- The source vertex
			Output:
				- Returns true if the current subgraph has cycles, false otherwise
		*/
		void DFSTopologicalSort(int sourceVertex); // i know both DFS can be done at the same time, but the code is clearer this way
		/*
			Performs a DFS from a source vertex; is used in determining the topological order of the vertices
			Input:
				- The vertex we start the DFS from
			Output:
				- The vertices are added to the topologicalOrder vector
		*/

		void topologicalSort();
		/*
			Performs a topological sorting of the vertices of the graph
			Input:
				- A vector which keeps track of the vertices that have been visited so far
			Output:
				- The topologicalOrder vector is properly filled
		*/

	public:
		int numberOfEdges;
		int numberOfVertices;

		Graph();
		/*
			Default constructor
			Input:
				- None
			Output:
				- The Graph object is built
		*/

		Graph(bool isOriented);
		/*
			Constructor
			Input:
				- Whether the graph is oriented or not
			Output:
				- The Graph object is built
		*/

		void resetGraph();
		/*
			Resets the content of the graph
			Input:
				- None
			Output:
				- The edges of the graph are deleted
		*/

		void addVertex();
		/*
			Adds a new vertex to the graph (with the index being the largest so far)
			Input:
				- None
			Output:
				- The vertex is added to the graph
		*/

		void addEdge(int sourceVertex, int destVertex);
		/*
			Adds an edge from sourceVertex to destVertex
			Input:
				- The source and the destination vertex
			Output:
				- The edge is added to the graph
		*/

		bool isEdge(int sourceVertex, int destVertex);
		/*
			Checks if the edge with the given end points exists
			Input:
				- The 2 end points of the edge
			Output:
				- Returns true if the edge exists, false otherwise
		*/

		bool checkIfAcyclic();
		/*
			Checks if the current graph is acyclic
			Input:
				- None
			Output:
				- Returns true is the graph is acyclic, false otherwise
		*/

		int countDistinctPaths(int sourceVertex, int destVertex);
		/*
			Counts the distinct paths from sourceVertex to destVertex
			Input:
				- The source/ destination vertex
			Output:
				- Throws exception if the vertices are invalid
				- Returns the number of distinct paths, otherwise
		*/

		virtual void loadGraphFromFile(std::string filePath);
		/*
			Loads a graph from a given file
			Input:
				- The path of the file we load from
			Output:
				- The graph contains the edges and vertices from the file
		*/

};