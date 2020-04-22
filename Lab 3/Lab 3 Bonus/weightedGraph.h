#pragma once
#include "graph.h"

class WeightedGraph : public Graph {
	private:
		std::unordered_map <Edge, int, CustomHashFunction> costEdges;
		
		// Dijkstra
		std::vector <int> minDistance;
		std::vector <int> minWalksCount;
		std::vector <int> minHeap;
		std::vector <int> heapPosition;

		void upHeap(int vertexPosition);
		void insertInHeap(int vertex, int& heapLength);
		void downHeap(int vertexPosition, int heapLength);
		int extractHeapTop(int& heapLength);
		void initialise();

	public:
		WeightedGraph();
		void addEdge(int sourceVertex, int destVertex, int edgeCost);
		void loadGraphFromFile(const std::string& filePath);
		void dijkstraMinWalksCount(int srcVertex);
		int getMinDistance(int destVertex);
		int getMinWalksCount(int destVertex);
		~WeightedGraph();
};