#include "graph.h"
#include <iostream>

using namespace std;

int Graph::getEdge(int srcVertex, int destVertex, vector <vector <Node>> v) {
	int position = 0;
	for (auto it = v[srcVertex].begin(); it != v[srcVertex].end(); ++it, ++position) {
		if (it->index == destVertex) {
			return position;
		}
	}
	return -1;
}

// deleted vertices will be marked with (-1, -1)
// isolated vertices will be marked with an empty vector
bool Graph::isActiveVertex(int vertex) {
	return vertex < nrTotalVertices && !(inEdges[vertex].size() == 1 and inEdges[vertex][0] == Node(-1, -1));
}

Graph::Graph() {
	nrActiveVertices = 0; // this will be decreased when removing a vertex
	nrTotalVertices = 0;
	nrEdges = 0;

	vector <Node> emptyVector;

	for (int i = 0; i < nrTotalVertices; i++) {
		inEdges.push_back(emptyVector);
		outEdges.push_back(emptyVector);
	}

	cout << "Done with the graph constructor\n";
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
	outEdges[srcVertex].push_back(Node(destVertex, 0));
	inEdges[destVertex].push_back(Node(srcVertex, 0));
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
	vector <Node> emptyVector;
	inEdges.push_back(emptyVector);
	outEdges.push_back(emptyVector);
	nrActiveVertices++;
	nrTotalVertices++;
}

void Graph::removeVertex(int vertex) {
	if (!isActiveVertex(vertex)) {
		throw 1;
	}

	vector <Node> temporary;

	temporary = inEdges[vertex];
	for (int index = 0; index < temporary.size(); index++) {
		removeEdge(temporary[index].index, vertex);
	}
	inEdges[vertex].clear();
	inEdges[vertex].push_back(Node(-1, -1));

	temporary = outEdges[vertex];
	for (int index = 0; index < temporary.size(); index++) {
		removeEdge(vertex, temporary[index].index);
	}
	outEdges[vertex].clear();
	outEdges[vertex].push_back(Node(-1, -1));

	nrActiveVertices--;
}
