#pragma once
#include "graph.h"

#define GRAPH_1K_WEIGHTED_ORIENTED "graph1k_w.txt"
#define GRAPH_1K_WEIGHTED_UNORIENTED "graph1k_w_uno.txt"

#define CURRENT_WEIGHTED_ORIENTED_GRAPH_FILE GRAPH_1K_WEIGHTED_ORIENTED
#define CURRENT_WEIGHTED_UNORIENTED_GRAPH_FILE GRAPH_1K_WEIGHTED_UNORIENTED

class WeightedGraph : public Graph {
	private:
		std::unordered_map <Edge, int, CustomHashFunction> costEdges;

	public:
		WeightedGraph();
		WeightedGraph(bool isOriented);
		void addEdge(int sourceVertex, int destVertex, int edgeCost);
		virtual bool addRandomEdge(int nrVertices);
		virtual void loadGraphFromFile();
		void saveGraphToFile();
		
		~WeightedGraph();
};