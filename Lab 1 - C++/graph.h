#pragma once
#include <vector>
#include "adjacentVertex.h"
#include "vectorIterator.h"

using namespace std;
typedef vector <vector <AdjacentVertex>> AdjacentVertexList;

class Graph {
	private:
		;

	protected:
		int nrActiveVertices;
		int nrTotalVertices;
		int nrEdges;
		AdjacentVertexList inEdges;
		AdjacentVertexList outEdges;

		int getEdge(int srcVertex, int destVertex, AdjacentVertexList v);
		
	public:
		Graph();
		void initEmptyGraph(int nrVertices);
		void clearGraph();
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