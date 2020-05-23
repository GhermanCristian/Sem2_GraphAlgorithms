#include "weightedGraph.h"
#include "disjointSetForest.h"
#include <iostream>
#include <algorithm>
#include <fstream>

WeightedGraph::WeightedGraph(){
	this->numberOfEdges = 0;
	this->numberOfVertices = 0;
}

void WeightedGraph::addVertex() {
	std::vector <int> emptyVector;
	inEdges.push_back(emptyVector);
	outEdges.push_back(emptyVector);
}

void WeightedGraph::resetGraph() {
	inEdges.clear();
	outEdges.clear();

	for (int i = 0; i < this->numberOfVertices; i++) {
		addVertex();
	}
}

void WeightedGraph::addEdge(int sourceVertex, int destVertex, int edgeCost){
	inEdges[destVertex].push_back(sourceVertex);
	outEdges[sourceVertex].push_back(destVertex);
	inEdges[sourceVertex].push_back(destVertex);
	outEdges[destVertex].push_back(sourceVertex);
	costEdges[Edge(sourceVertex, destVertex)] = edgeCost;
}

void WeightedGraph::loadGraphFromFile(std::string filePath) {
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

bool WeightedGraph::selectEdgesRec(int positionInEdgeList, int cycleLength) {
	Edge currentEdge = this->allEdges[positionInEdgeList];
	int sourceVertex = currentEdge.srcVertex;
	int destVertex = currentEdge.destVertex;
	bool result = false;

	this->hamPathEdges.push_back(currentEdge);
	this->hamPathCost += this->costEdges[currentEdge];
	this->visitCount[sourceVertex]++;
	this->visitCount[destVertex]++;

	if (cycleLength == this->numberOfVertices - 1) {
		return true;
	}

	for (int i = positionInEdgeList + 1; i < this->allEdges.size(); i++) {
		if (this->visitCount[this->allEdges[i].srcVertex] < 2 and this->visitCount[this->allEdges[i].destVertex] < 2) {
			result = selectEdgesRec(i, cycleLength + 1);
			if (result == true) {
				return true;
			}
		}
	}

	this->hamPathEdges.pop_back();
	this->hamPathCost -= this->costEdges[currentEdge];
	this->visitCount[sourceVertex]--;
	this->visitCount[destVertex]--;

	return result;
}

void WeightedGraph::approximateTSPSortingEdges(){
	this->allEdges.clear();
	for (auto currentEdge : costEdges) {
		this->allEdges.push_back(currentEdge.first);
	}
	std::sort(this->allEdges.begin(), this->allEdges.end(), [this](const Edge& a, const Edge& b) {return costEdges[a] < costEdges[b]; });

	this->visitCount.clear();
	for (int i = 0; i < this->numberOfVertices; i++) {
		this->visitCount.push_back(0);
	}

	this->hamPathEdges.clear();
	this->hamPathCost = 0;

	this->selectEdgesRec(0, 0);
}

int WeightedGraph::getEdgeCost(int a, int b){
	if (this->costEdges.find(Edge(a, b)) != this->costEdges.end()) {
		return this->costEdges[Edge(a, b)];
	}
	return this->costEdges[Edge(b, a)];
}

bool WeightedGraph::DFSNearestNeighbour(int sourceVertex, int cycleLength){
	this->visited[sourceVertex] = true;
	std::vector<int> outboundNeighbours = outEdges[sourceVertex];
	std::sort(outboundNeighbours.begin(), outboundNeighbours.end(), [this, sourceVertex](int a, int b) {return getEdgeCost(sourceVertex, a) < getEdgeCost(sourceVertex, b); });
	bool hasFoundOriginalVertex = false;

	for (auto neighbour : outboundNeighbours) {
		if (neighbour == this->originalVertex and cycleLength == this->numberOfVertices - 1) {
			this->hamPathVertices.push_back(sourceVertex);
			this->hamPathCost += this->getEdgeCost(sourceVertex, neighbour);
			return true; // propel the result up the DFS tree
		}
		else if (visited[neighbour] == false) {
			hasFoundOriginalVertex = DFSNearestNeighbour(neighbour, cycleLength + 1);
			if (hasFoundOriginalVertex) {
				this->hamPathVertices.push_back(sourceVertex);
				this->hamPathCost += this->getEdgeCost(sourceVertex, neighbour);
				return true; // propel the result up the DFS tree
			}
		}
	}

	this->visited[sourceVertex] = false;
	return hasFoundOriginalVertex;
}

void WeightedGraph::approximateTSPNearestNeighbour(){
	this->originalVertex = 0;
	this->hamPathCost = 0;

	this->visited.clear();
	for (int i = 0; i < this->numberOfVertices; i++) {
		this->visited.push_back(false);
	}

	this->hamPathVertices.clear();
	this->DFSNearestNeighbour(this->originalVertex, 0);
}

const std::vector<int>& WeightedGraph::getHamPathVertices() {
	return this->hamPathVertices;
}

const std::vector<Edge>& WeightedGraph::getHamPathEdges(){
	return this->hamPathEdges;
}

int WeightedGraph::getHamPathCost(){
	return this->hamPathCost;
}

WeightedGraph::~WeightedGraph(){
	;
}
