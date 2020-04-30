#pragma once
#include <vector>
#include <fstream>
const int NON_EXISTENT = -111111;

class Graph {
	protected:
		bool isOriented;
		std::vector < std::vector  <int> > inEdges;
		std::vector < std::vector  <int> > outEdges;

	public:
		int numberOfEdges;
		int numberOfVertices;

		Graph();
		Graph(bool isOriented);
		void resetGraph();
		void addVertex();
		void addEdge(int sourceVertex, int destVertex);
		bool isEdge(int sourceVertex, int destVertex);
		virtual void loadGraphFromFile(std::string filePath);
};