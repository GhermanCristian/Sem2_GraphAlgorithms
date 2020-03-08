#pragma once
#include <vector>
#include "node.h"
#include "vectorIterator.h"

using namespace std;

class Graph {
	private:
		;

	protected:
		int nrActiveVertices;
		int nrTotalVertices;
		int nrEdges;
		vector <vector <Node>> inEdges;
		vector <vector <Node>> outEdges;

		int getEdge(int srcVertex, int destVertex, vector <vector <Node>> v);
		

	public:
		Graph();
		int getTotalNrVertices();
		int getNrEdges();
		int getNrVertices();
		bool isActiveVertex(int vertex);
		bool isEdge(int srcVertex, int destVertex);
		int getInDegree(int vertex);
		int getOutDegree(int vertex);
		VectorIterator inEdgesIterator(int vertex);
		VectorIterator outEdgesIterator(int vertex);
		void addEdge(int srcVertex, int destVertex);
		void removeEdge(int srcVertex, int destVertex);
		void addVertex();
		void removeVertex(int vertex);
};