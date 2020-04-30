#pragma once
#include "graph.h"
#include "edge.h"
#include "customHash.h"
#include <unordered_map>

class WeightedGraph : public Graph {
	private:
		std::unordered_map <Edge, int, CustomHashFunction> costEdges;
		std::vector <Edge> minimumSpanningTreeEdges;
		
		bool edgeCostCompareFunction(const Edge& a, const Edge& b);
		int getEdgeCost(int a, int b);

	public:
		WeightedGraph();
		WeightedGraph(bool isOriented);
		void addEdge(int sourceVertex, int destVertex, int edgeCost);
		virtual void loadGraphFromFile(std::string filePath);
		int getMSTCostKruskal();
		const std::vector <Edge>& getMSTEdgesKruskal();
		~WeightedGraph();
};