#pragma once
#include "graph.h"
#include "edge.h"
#include "customHash.h"

class WeightedGraph : public Graph {
	private:
		std::unordered_map <Edge, int, CustomHashFunction> costEdges;

	public:
		WeightedGraph();
		WeightedGraph(bool isOriented);
		void addEdge(int sourceVertex, int destVertex, int edgeCost);
		virtual void loadGraphFromFile(std::string filePath);
		~WeightedGraph();
};