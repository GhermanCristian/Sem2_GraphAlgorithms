#pragma once
#include "graph.h"
#include <unordered_map>
#include "customHash.h"

class WeightedGraph : public Graph {
	unordered_map <Edge, int, CustomHashFunction> costEdges;

	public:
		WeightedGraph();
		void clearGraph();
		int getEdgeCost(int srcVertex, int destVertex);
		void modifyEdgeCost(int srcVertex, int destVertex, int newCost);
		void addEdge(int srcVertex, int destVertex, int cost);
		void removeEdge(int srcVertex, int destVertex);
		void printGraph();
		void removeVertex(int vertex);
		WeightedGraph(const WeightedGraph& originalGraph);
};