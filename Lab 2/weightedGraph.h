#pragma once
#include "graph.h"

class WeightedGraph : public Graph {
	private:
		std::unordered_map <Edge, int, CustomHashFunction> costEdges;

	public:
		WeightedGraph();
		void addEdge(int sourceVertex, int destVertex, int edgeCost);
		void generateRandomGraph(int nrVertices, int nrEdges);
		void loadGraphFromFile();
		void saveGraphToFile();
		
		~WeightedGraph();
};