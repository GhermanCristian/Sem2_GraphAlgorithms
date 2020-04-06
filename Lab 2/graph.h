#pragma once
#include <vector>
#include <unordered_map>
#include <fstream>
#include "edge.h"
#include "customHash.h"

#define GRAPH_1K_UNWEIGHTED_ORIENTED "graph1k_unw.txt"
#define GRAPH_1K_UNWEIGHTED_UNORIENTED "graph1k_unw_uno.txt"
#define GRAPH_30K_UNWEIGHTED_UNORIENTED "graph30k_unw_uno.txt"

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
		int globalIndex; // also used in biComp
		std::vector <int> inStack;
		std::vector <int> validNodeStack;
		std::vector <int> depth; // also used in biComp
		std::vector <int> lowLink; // also used in biComp
		std::vector < std::vector <int> > SCCList;
		void pushToStack(int newVertexIndex);
		/*
			Pushes a vertex to the validNodeStack
			Input:
				- The global index of the the vertex we want to add
			Output:
				- The value is added to the stack
				- The value is marked as being "inStack"
		*/

		void popFromStack();
		/*
			Removes the last value inserted in the stack
			Input:
				- None
			Output:
				- The last value is removed from the stack
				- The last value is marked as removed from the stack
		*/
		
		void tarjanDFS(int srcVertex);
		/*
			Performs a DFS starting in a given vertex
			Input:
				- The vertex we start from
			Output:
				- 
		*/

		std::vector <int> newSCC(int SCCRoot);
		/*
			Determines the strongly-connected component which starts from a given vertex
			Input:
				- The vertex we start from
			Output:
				- Returns a list of vertices which are part of the current SCC
		*/


		// biconnected
		std::vector < std::vector <int> > biCompList;
		std::vector <Edge> edgeStack;
		std::vector <int> newBiComp(int srcVertex, int neighbour);
		void biCompDFS(int srcVertex);

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
		virtual void loadGraphFromFile();
		void saveGraphToFile();

		// BFS
		void BFS(int srcVertex, int destVertex);
		/*
			Performs a BFS starting from srcVertex, which stops when encountering destVertex
			Input:
				- The vertex we start from and the one we end up with
			Output:
				- The path from srcVertex to destVertex (and its length) is determined
		*/

		int getDistanceToVertex(int destVertex);
		/*
			Determines the distance from the previous source vertex to destVertex
			Input:
				- The function "BFS" has to have been called before this
				- The destination vertex
			Output:
				- The distance from the previous source vertex to destVertex, or a negative value if there is
				no path
		*/

		std::vector <int> getPathToVertex(int srcVertex, int destVertex);
		/*
			Determines the path from srcVertex to destVertex
			Input:
				- The function "BFS" has to have been called before this
				- The start and the destination vertices
			Output:
				- Returns a list of vertices which form the path
		*/

		// SCC
		void computeSCC();
		/*
			Determines the strongly-connected components of the graph
			Input:
				- None
			Output:
				- The strongly-connected components are calculated
		*/

		int getSCCCount();
		/*
			Determines the number of strongly-connected components
			Input:
				- The function "computeSCC" has to have been called prior to this 
			Output:
				- Returns the number of SCCs
		*/

		std::vector < std::vector <int> > getSCCList();
		/*
			Determines the vertices in the current SCC
			Input:
				- The function "computeSCC" has to have been called prior to this 
			Output:
				- Returns the list of strongly-connected components in the graph
		*/


		// biconnected
		void computeBiComp();
		/*
			Determines the biconnected components of the graph
			Input:
				- None
			Output:
				- The biconnected components of the graph are computed
		*/

		int getBiCompCount();
		/*
			Determines the number of biconnected components from the graph
			Input:
				- The function "computeBiComp" has to have been called prior to this
			Output:
				- Returns the number of biconnected components from the graph
		*/

		std::vector < std::vector <int> > getBiCompList();
		/*
			Determines the list of biconnected components from the graph
			Input:
				- The function "computeBiComp" has to have been called prior to this
			Output:
				- Returns the list of biconnected components from the graph
		*/
};