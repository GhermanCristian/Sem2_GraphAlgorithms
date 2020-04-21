#include "weightedGraph.h"
#include <fstream>
#include <iostream>

void WeightedGraph::initialiseEmptyGraph(){
	std::vector <int> emptyRow;
	for (int i = 0; i < this->numberVertices; i++) {
		emptyRow.push_back(NONEXISTENT_EDGE);
	}
	for (int i = 0; i < this->numberVertices; i++) {
		this->weights.push_back(emptyRow);
		this->minimumDistance.push_back(emptyRow);
		this->aux.push_back(emptyRow);
		this->weights[i][i] = 0;
	}
}

void WeightedGraph::multiplyMatrices(Matrix& first, Matrix& second){
	for (int row = 0; row < this->numberVertices; row++) {
		for (int column = 0; column < this->numberVertices; column++) {
			aux[row][column] = NONEXISTENT_EDGE;
			for (int pos = 0; pos < this->numberVertices; pos++) {
				if (first[row][pos] != NONEXISTENT_EDGE and second[pos][column] != NONEXISTENT_EDGE and aux[row][column] > first[row][pos] + second[pos][column]) {
					aux[row][column] = first[row][pos] + second[pos][column];
				}
			}
		}
	}

	for (int row = 0; row < this->numberVertices; row++) {
		for (int column = 0; column < this->numberVertices; column++) {
			first[row][column] = aux[row][column];
		}
	}
}

void WeightedGraph::displayMatrix(const Matrix& currentMatrix){
	for (int row = 0; row < this->numberVertices; row++) {
		for (int column = 0; column < this->numberVertices; column++) {
			if (currentMatrix[row][column] == NONEXISTENT_EDGE) {
				std::cout << "INF" << "\t";
			}
			else {
				std::cout << currentMatrix[row][column] << "\t";
			}
		}
		std::cout << "\n";
	}
}

WeightedGraph::WeightedGraph(std::string filePath){
	int sourceVertex;
	int destVertex;
	int edgeCost;
	
	std::ifstream in(filePath);
	in >> this->numberVertices >> this->numberEdges;
	this->initialiseEmptyGraph();

	for (int edge = 0; edge < this->numberEdges; edge++) {
		in >> sourceVertex >> destVertex >> edgeCost;
		addEdge(sourceVertex, destVertex, edgeCost);
	}

	in.close();
}

void WeightedGraph::addEdge(int sourceVertex, int destVertex, int costEdge){
	if (sourceVertex < 0 or destVertex < 0 or sourceVertex >= this->numberVertices or destVertex >= this->numberVertices) {
		throw std::exception("Invalid vertices");
	}
	this->weights[sourceVertex][destVertex] = costEdge;
}

void WeightedGraph::computeAPSP(){
	for (int row = 0; row < this->numberVertices; row++) {
		for (int column = 0; column < this->numberVertices; column++) {
			this->minimumDistance[row][column] = this->weights[row][column];
			this->aux[row][column] = 0;
		}
	}

	std::cout << "Path of length <= 1\n";
	this->displayMatrix(minimumDistance);
	std::cout << "\n";

	for (int pathLength = 2; pathLength < this->numberVertices; pathLength++) {
		this->multiplyMatrices(minimumDistance, weights);

		std::cout << "Path of length <= " << pathLength << "\n";
		this->displayMatrix(minimumDistance);
		std::cout << "\n";
	}
}

int WeightedGraph::getMinimumDistance(int sourceVertex, int destVertex){
	if (sourceVertex < 0 or destVertex < 0 or sourceVertex >= this->numberVertices or destVertex >= this->numberVertices) {
		throw std::exception("Invalid vertices");
	}

	return this->minimumDistance[sourceVertex][destVertex];
}
