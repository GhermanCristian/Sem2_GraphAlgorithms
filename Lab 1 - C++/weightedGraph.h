#pragma once
#include "graph.h"
#include <unordered_map>
#include "customHash.h"

class WeightedGraph : public Graph {
	public:
		unordered_map <Edge, int, CustomHashFunction> costEdges;

		WeightedGraph();
		void clearGraph();
		int getEdgeCost(int srcVertex, int destVertex, bool doChecks = true);
		void modifyEdgeCost(int srcVertex, int destVertex, int newCost, bool doChecks = true);
		void addEdge(int srcVertex, int destVertex, int cost, bool doChecks = true);
		void removeEdge(int srcVertex, int destVertex);
		void printGraph();
		void removeVertex(int vertex);
		WeightedGraph(const WeightedGraph& originalGraph);
		WeightedGraph& operator = (const WeightedGraph& originalGraph);
};