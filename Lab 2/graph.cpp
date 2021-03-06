#include "graph.h"
#include <queue>
#include <iostream>

Graph::Graph() {
	this->numberOfEdges = 0;
	this->numberOfVertices = 0;
	this->globalIndex = 0;
	this->isOriented = true;
}

Graph::Graph(bool isOriented) {
	this->numberOfEdges = 0;
	this->numberOfVertices = 0;
	this->globalIndex = 0;
	this->isOriented = isOriented;
}

void Graph::resetGraph() {
	inEdges.clear();
	outEdges.clear();

	for (int i = 0; i < this->numberOfVertices; i++) {
		addVertex();
	}
}

void Graph::addVertex() {
	std::vector <int> emptyVector;
	inEdges.push_back(emptyVector);
	outEdges.push_back(emptyVector);
}

void Graph::addEdge(int sourceVertex, int destVertex){
	inEdges[destVertex].push_back(sourceVertex);
	outEdges[sourceVertex].push_back(destVertex);
	if (this->isOriented == false) {
		inEdges[sourceVertex].push_back(destVertex);
		outEdges[destVertex].push_back(sourceVertex);
	}
}

bool Graph::isEdge(int sourceVertex, int destVertex){
	for (auto iter : inEdges[destVertex]) {
		if (iter == sourceVertex) {
			return true;
		}
	}

	return false;
}

bool Graph::addRandomEdge(int nrVertices){
	int srcVertex = rand() % nrVertices;
	int destVertex = rand() % nrVertices;

	if (srcVertex == destVertex and isOriented == false) {
		return false;
	}

	if (this->isEdge(srcVertex, destVertex) == false) {
		this->addEdge(srcVertex, destVertex);
		return true;
	}

	return false;
}

void Graph::generateRandomGraph(int nrVertices, int nrEdges) {
	if (nrVertices * nrVertices < nrEdges) {
		return;
	}

	this->numberOfVertices = nrVertices;
	this->numberOfEdges = nrEdges;
	this->resetGraph();

	int nrExistingEdges = 0;
	while (nrExistingEdges < nrEdges) {
		nrExistingEdges += addRandomEdge(nrVertices);
	}
}

void Graph::loadGraphFromFile() {
	int sourceVertex, destVertex;
	std::string currentFile;

	// we assume the input is valid
	if (this->isOriented) {
		currentFile = CURRENT_ORIENTED_GRAPH_FILE;
	}
	else {
		currentFile = CURRENT_UNORIENTED_GRAPH_FILE;
	}
	std::cout << "current file: " << currentFile << "\n";

	std::ifstream in(currentFile);
	in >> this->numberOfVertices >> this->numberOfEdges;
	this->resetGraph();
	for (int i = 0; i < this->numberOfEdges; i++) {
		in >> sourceVertex >> destVertex;
		this->addEdge(sourceVertex, destVertex);
	}

	in.close();
}

void Graph::saveGraphToFile() {
	std::string currentFile;

	// we assume the input is valid
	if (this->isOriented) {
		currentFile = CURRENT_ORIENTED_GRAPH_FILE;
	}
	else {
		currentFile = CURRENT_UNORIENTED_GRAPH_FILE;
	}

	std::ofstream out(currentFile);
	out << this->numberOfVertices << " " << this->numberOfEdges << "\n";
	for (int srcVertex = 0; srcVertex < this->numberOfVertices; srcVertex++) {
		for (auto destVertex : outEdges[srcVertex]) {
			out << srcVertex << " " << destVertex << "\n";
		}
	}
	out.close();
}

void Graph::BFS(int srcVertex, int destVertex) {
	if (srcVertex >= this->numberOfVertices or destVertex >= this->numberOfVertices) {
		throw std::exception("Invalid vertices");
	}

	queue <int> availableVertices;
	bool foundVertex = false;
	int nextVertex;

	parent.clear();
	parent[srcVertex] = NON_EXISTENT;

	distanceFromSource.clear();
	for (int i = 0; i < this->numberOfVertices; i++) {
		distanceFromSource[i] = NON_EXISTENT;
	}
	distanceFromSource[srcVertex] = 0;

	availableVertices.push(srcVertex);

	while (!availableVertices.empty() and foundVertex == false) {
		nextVertex = availableVertices.front();

		for (auto neighbour : outEdges[nextVertex]) {
			if (distanceFromSource[neighbour] == NON_EXISTENT) {
				distanceFromSource[neighbour] = distanceFromSource[nextVertex] + 1;
				availableVertices.push(neighbour);
				parent[neighbour] = nextVertex;
			}

			if (neighbour == destVertex) {
				foundVertex = true;
			}
		}

		availableVertices.pop();
	}
}

int Graph::getDistanceToVertex(int destVertex) {
	if (destVertex >= this->numberOfVertices) {
		throw std::exception("Invalid vertex");
	}

	return distanceFromSource[destVertex];
}

std::vector<int> Graph::getPathToVertex(int srcVertex, int destVertex) {
	if (distanceFromSource[destVertex] == NON_EXISTENT) {
		return std::vector<int>();
	}

	int currentVertex = destVertex;
	std::vector <int> pathToVertex;

	for (int currentVertex = destVertex; currentVertex != srcVertex; currentVertex = parent[currentVertex]) {
		pathToVertex.push_back(currentVertex);
	}
	pathToVertex.push_back(srcVertex);
	// I could let the path be in reverse, and then just print from end to beginning
	std::reverse(pathToVertex.begin(), pathToVertex.end());

	return pathToVertex;
}

void Graph::pushToStack(int newVertexIndex) {
	validNodeStack.push_back(newVertexIndex);
	inStack[newVertexIndex] = true;
}

void Graph::popFromStack() {
	inStack[validNodeStack.back()] = false;
	validNodeStack.pop_back();
}

std::vector <int> Graph::newSCC(int SCCRoot) {
	std::vector <int> currentSCC;

	while (SCCRoot != validNodeStack.back()) {
		depth[validNodeStack.back()] = depth[SCCRoot];
		currentSCC.push_back(validNodeStack.back());
		popFromStack();
	}
	currentSCC.push_back(SCCRoot);
	popFromStack();

	return currentSCC;
}

void Graph::tarjanDFS(int srcVertex) {
	depth[srcVertex] = lowLink[srcVertex] = ++globalIndex;
	pushToStack(srcVertex);

	for (auto neighbour : outEdges[srcVertex]) {
		if (depth[neighbour] == 0) {
			tarjanDFS(neighbour);
			lowLink[srcVertex] = min(lowLink[srcVertex], lowLink[neighbour]);
		}

		else if (inStack[neighbour] == true) {
			lowLink[srcVertex] = min(lowLink[srcVertex], depth[neighbour]);
		}
	}

	if (lowLink[srcVertex] == depth[srcVertex]) {
		SCCList.push_back(newSCC(srcVertex));
	}
}

void Graph::computeSCC() {
	depth.clear();
	lowLink.clear();
	inStack.clear();
	validNodeStack.clear();
	SCCList.clear();
	globalIndex = 0;

	for (int vertex = 0; vertex < this->numberOfVertices; vertex++) {
		depth.push_back(0);
		lowLink.push_back(0);
		inStack.push_back(false);
	}

	for (int vertex = 0; vertex < this->numberOfVertices; vertex++) {
		if (depth[vertex] == 0) {
			tarjanDFS(vertex);
		}
	}
}

int Graph::getSCCCount() {
	return SCCList.size();
}

std::vector<std::vector<int>> Graph::getSCCList() {
	return SCCList;
}

std::vector<int> Graph::newBiComp(int srcVertex, int neighbour){
	std::vector <int> currentBiComp;
	Edge currentEdge(srcVertex, neighbour);

	while (currentEdge != edgeStack.back()) {
		currentBiComp.push_back(edgeStack.back().destVertex);
		edgeStack.pop_back();
	}

	edgeStack.pop_back(); // we also have to remove (srcVertex, neighbour) from the stack
	currentBiComp.push_back(srcVertex);
	currentBiComp.push_back(neighbour);

	return currentBiComp;
}

void Graph::biCompDFS(int srcVertex){
	lowLink[srcVertex] = depth[srcVertex] = ++globalIndex;

	for (auto neighbour : outEdges[srcVertex]) {
		if (depth[neighbour] == 0) {
			edgeStack.push_back(Edge(srcVertex, neighbour));
			biCompDFS(neighbour);

			if (lowLink[neighbour] >= depth[srcVertex]) {
				biCompList.push_back(newBiComp(srcVertex, neighbour));
			}

			lowLink[srcVertex] = min(lowLink[srcVertex], lowLink[neighbour]);
		}

		else {
			lowLink[srcVertex] = min(lowLink[srcVertex], depth[neighbour]);
		}

	}
}

void Graph::computeBiComp(){
	depth.clear();
	lowLink.clear();
	edgeStack.clear();
	biCompList.clear();
	globalIndex = 0;

	for (int vertex = 0; vertex < this->numberOfVertices; vertex++) {
		depth.push_back(0);
		lowLink.push_back(0);
	}

	for (int vertex = 0; vertex < this->numberOfVertices; vertex++) {
		if (depth[vertex] == 0) {
			biCompDFS(vertex);
		}
	}
}

int Graph::getBiCompCount(){
	return biCompList.size();
}

std::vector<std::vector<int>> Graph::getBiCompList(){
	return biCompList;
}

