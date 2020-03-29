#include "graph.h"
#include <iostream>

using namespace std;

int Graph::getEdge(int srcVertex, int destVertex, AdjacentVertexList v) {
	int position = 0;

	if (!isActiveVertex(srcVertex) or !isActiveVertex(destVertex)) {
		return -1;
	}

	for (VectorIterator iter(v[srcVertex]); iter.isValid(); ++iter, ++position) {
		if ((*iter) == destVertex) {
			return position;
		}
	}

	return -1;
}

// deleted vertices will be marked with -1
// isolated vertices will be marked with an empty vector
bool Graph::isActiveVertex(int vertex) {
	return vertex < nrTotalVertices and !(inEdges[vertex].size() == 1 and inEdges[vertex][0] == -1);
}

Graph::Graph() {
	nrActiveVertices = 0; // this will be decreased when removing a vertex
	nrTotalVertices = 0; // this will not ^
	nrEdges = 0;
	cout << "Done with the graph constructor\n";
}

void Graph::initEmptyGraph(int nrVertices){
	vector <int> emptyVector;
	for (int i = 0; i < nrVertices; i++) {
		inEdges.push_back(emptyVector);
		outEdges.push_back(emptyVector);
	}
}

int Graph::getNrEdges() {
	return nrEdges;
}

int Graph::getTotalNrVertices() {
	return nrTotalVertices;
}

int Graph::getNrVertices() {
	return nrActiveVertices;
}

bool Graph::isEdge(int srcVertex, int destVertex) {
	return (getEdge(srcVertex, destVertex, outEdges) != -1);
}

int Graph::getInDegree(int vertex) {
	return inEdges[vertex].size();
}

int Graph::getOutDegree(int vertex) {
	return outEdges[vertex].size();
}

VectorIterator Graph::inEdgesIterator(int vertex) {
	return VectorIterator(inEdges[vertex]);
}

VectorIterator Graph::outEdgesIterator(int vertex) {
	return VectorIterator(outEdges[vertex]);
}

void Graph::addEdge(int srcVertex, int destVertex) {
	if (isEdge(srcVertex, destVertex) == true) {
		throw 1;
	}

	outEdges[srcVertex].push_back(destVertex);
	inEdges[destVertex].push_back(srcVertex);
	nrEdges++;
}

void Graph::removeEdge(int srcVertex, int destVertex) {
	int inEdgePos = getEdge(destVertex, srcVertex, inEdges);
	int outEdgePos = getEdge(srcVertex, destVertex, outEdges);

	if (inEdgePos == -1 or outEdgePos == -1) {
		throw 1;
	}

	outEdges[srcVertex].erase(outEdges[srcVertex].begin() + outEdgePos);
	inEdges[destVertex].erase(inEdges[destVertex].begin() + inEdgePos);
	nrEdges--;
}

void Graph::addVertex() {
	vector <int> emptyVector;

	inEdges.push_back(emptyVector);
	outEdges.push_back(emptyVector);
	nrActiveVertices++;
	nrTotalVertices++;
}

void Graph::removeVertex(int vertex) {
	if (!isActiveVertex(vertex)) {
		throw 1;
	}

	vector <int> temporary;

	temporary = inEdges[vertex];
	for (VectorIterator iter(temporary); iter.isValid(); ++iter) {
		removeEdge((*iter), vertex);
	}
	inEdges[vertex].clear();

	temporary = outEdges[vertex];
	for (VectorIterator iter(temporary); iter.isValid(); ++iter) {
		removeEdge(vertex, (*iter));
	}
	outEdges[vertex].clear();

	inEdges[vertex].push_back(-1);
	outEdges[vertex].push_back(-1);

	nrActiveVertices--;
}

void Graph::clearGraph() {
	nrActiveVertices = 0;
	nrTotalVertices = 0;
	nrEdges = 0;
	inEdges.clear();
	outEdges.clear();
}
