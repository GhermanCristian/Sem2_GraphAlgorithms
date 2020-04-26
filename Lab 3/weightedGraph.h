#pragma once
#include <vector>
#include <string>

const int NONEXISTENT_EDGE = 111111111;
typedef std::vector < std::vector <int> > Matrix;

class WeightedGraph{
	private:
		int numberVertices;
		int numberEdges;
		Matrix weights; // [i][j] = weight of the edge from i to j
		Matrix minimumDistance; // [i][j] = minimum distance from i to j
		Matrix aux; // used in multiplications
		Matrix intermediateVertex;

		void resetAuxMatrix();
		/*
			Resets the aux matrix
		*/

		void initialiseEmptyGraph();
		/*
			Resets the weights, minimumDistance and aux matrices
			Input:
				- None
			Output:
				- The values of the three matrices are reset
		*/

		bool multiplyMatrices(Matrix& first, Matrix& second);
		/*
			Performs the matrix multiplication algorithm for determining the minimum distance
			Input:
				- The two matrices
			Output:
				- "first" will store the new minimum distances
				- Returns true if there has been at least one distance improvement, false otherwise
		*/

		void displayMatrix(const Matrix& currentMatrix);
		/*
			Displays a matrix on the screen
			Input:
				- The matrix we want to display
			Output:
				- The matrix is display to the screen
		*/

	public:
		WeightedGraph(std::string filePath);
		/*
			Constructor for the WeightedGraph class
			Input:
				- The path of the file we load the graph from
			Output:
				- The graph is created and loaded with the content of the given file
		*/

		void addEdge(int sourceVertex, int destVertex, int costEdge);
		/*
			Adds an edge from sourceVertex to destVertex, with a given cost
			Input:
				- The 2 ends of the edge and its cost
			Output:
				- The edge is added
		*/

		bool computeAPSP();
		/*
			The All Pair Shortest Path algorithm
			Input:
				- None
			Output:
				- Computes the minimum distance between each pair of vertices
				- Displays all the intermediary distance matrices
				- Returns true if the graph contains a negative weight cycle, false otherwise
		*/

		int getMinimumDistance(int sourceVertex, int destVertex);
		/*
			Determines the minimum distance between 2 given vertices
			Input:
				- The two vertices
			Output:
				- Returns the minimum distance
				- Throws an exception if any of the vertices doesn't exist
		*/

		std::vector < int > getMinimumWalk(int sourceVertex, int destVertex);
		/*
			Determines the minimum walk between 2 given vertices
			Input:
				- The two vertices
			Output:
				- Returns the minimum walk
				- Throws an exception if any of the vertices doesn't exist
		*/
};

