#include "weightedGraph.h"
#include <iostream>

void WeightedGraph::upHeap(int vertexPosition){
	int key = minHeap[vertexPosition];

	while (vertexPosition and vertexPosition / 2 >= 0 and minDistance[minHeap[vertexPosition / 2]] > minDistance[key]) {
		minHeap[vertexPosition] = minHeap[vertexPosition / 2];
		heapPosition[ minHeap[vertexPosition] ] = vertexPosition;
		vertexPosition /= 2;
	}

	minHeap[vertexPosition] = key;
	heapPosition[minHeap[vertexPosition]] = vertexPosition;
}

void WeightedGraph::insertInHeap(int vertex, int& heapLength) {
	minHeap[heapLength] = vertex;
	heapPosition[vertex] = heapLength;
	upHeap(heapLength);
	heapLength++;
}

void WeightedGraph::downHeap(int vertexPosition, int heapLength){
	int successor = -1;

	while (successor != vertexPosition) {
		successor = vertexPosition;

		if (successor * 2 < heapLength and minDistance[minHeap[vertexPosition]] > minDistance[minHeap[successor * 2]]) {
			vertexPosition = successor * 2;
		}
		if (successor * 2 + 1 < heapLength and minDistance[minHeap[vertexPosition]] > minDistance[minHeap[successor * 2 + 1]]) {
			vertexPosition = successor * 2 + 1;
		}

		swap(minHeap[successor], minHeap[vertexPosition]);
		heapPosition[minHeap[successor]] = successor;
		heapPosition[minHeap[vertexPosition]] = vertexPosition;
	}
}

int WeightedGraph::extractHeapTop(int& heapLength){
	int top = minHeap[0];

	heapPosition[top] = -1;
	minHeap[0] = minHeap[--heapLength];
	heapPosition[minHeap[0]] = 0;
	downHeap(0, heapLength);

	return top;
}

void WeightedGraph::initialise(){
	this->minDistance.clear();
	this->walkCount.clear();
	this->minHeap.clear();
	this->heapPosition.clear();
	for (int i = 0; i < this->numberOfVertices; i++) {
		this->minDistance.push_back(NON_EXISTENT);
		this->walkCount.push_back(0);
		this->minHeap.push_back(0);
		this->heapPosition.push_back(-1);
	}
}

WeightedGraph::WeightedGraph() : Graph(){
	;
}

void WeightedGraph::addEdge(int sourceVertex, int destVertex, int edgeCost){
	Graph::addEdge(sourceVertex, destVertex);
	costEdges[Edge(sourceVertex, destVertex)] = edgeCost;
}

void WeightedGraph::loadGraphFromFile(const std::string& filePath) {
	int sourceVertex, destVertex, edgeCost;

	std::ifstream in(filePath);
	in >> this->numberOfVertices >> this->numberOfEdges;
	this->resetGraph();
	for (int i = 0; i < this->numberOfEdges; i++) {
		in >> sourceVertex >> destVertex >> edgeCost;
		this->addEdge(sourceVertex, destVertex, edgeCost);
	}

	in.close();
}

void WeightedGraph::dijkstraMinWalksCount(int srcVertex){
	if (srcVertex < 0 or srcVertex >= this->numberOfVertices) {
		throw std::exception("Invalid vertex");
	}

	int heapLength = 0, top, cost;

	initialise();
	this->minDistance[srcVertex] = 0;
	this->walkCount[srcVertex] = 1;
	insertInHeap(srcVertex, heapLength);

	while (heapLength > 0) {
		top = extractHeapTop(heapLength);

		for (auto vertex : outEdges[top]) {
			cost = costEdges[Edge(top, vertex)];

			if (minDistance[vertex] > minDistance[top] + cost) {
				minDistance[vertex] = minDistance[top] + cost;
				walkCount[vertex] = walkCount[top];

				if (heapPosition[vertex] != -1) {
					upHeap(heapPosition[vertex]);
				}
				else {
					insertInHeap(vertex, heapLength);
				}
			}

			else if (minDistance[vertex] == minDistance[top] + cost) {
				walkCount[vertex] += walkCount[top];
			}
		}
	}
}

WeightedGraph::~WeightedGraph(){
	;
}
