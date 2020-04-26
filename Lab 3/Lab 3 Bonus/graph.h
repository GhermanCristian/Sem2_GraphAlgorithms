#pragma once
#include <vector>
#include <unordered_map>
#include <fstream>
#include "edge.h"
#include "customHash.h"

const int NON_EXISTENT = 11111111;

class Graph {
	private:
		std::vector < int > topologicalOrder; // will contain the vertices of the graph sorted in topological order
		std::vector < bool > visited;
		void DFSTopologicalSort(int srcVertex);
		/*
			Performs a DFS from a source vertex, and which is used in determining the topological order of the vertices
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

	protected:
		std::vector < std::vector <int> > inEdges;
		std::vector < std::vector <int> > outEdges;
		std::vector < int > walkCount; // counts the number of walks from a given sourceVertex to all the other vertices

	public:
		int numberOfEdges;
		int numberOfVertices;

		Graph();
		/*
			Constructor
			Input:
				- None
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

		void loadGraphFromFile(const std::string& filePath);
		/*
			Loads a graph from a given file
			Input:
				- The path of the file we load from
			Output:
				- The graph contains the edges and vertices from the file
		*/

		void determineWalks(int sourceVertex);
		/*
			Determines the number of walks from sourceVertex to all the other vertices
			Input:
				- The source vertex
				- The topologicalOrder vector, which is filled
			Output:
				- The walkCount vector is filled
		*/

		int getWalkCount(int destVertex);
		/*
			Determines the number of walks from the previous source vertex to destVertex
			Input:
				- The destination vertex
				- The walkCount vector has to be filled prior to this call
			Output:
				- Returns the number of walks from sourceVertex to destVertex
				- Throws an exception if any of the vertices don't exist
		*/

};