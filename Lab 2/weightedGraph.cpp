#include "weightedGraph.h"
#include <queue>

WeightedGraph::WeightedGraph(){
	numberOfEdges = 0;
	numberOfVertices = 0;
}

void WeightedGraph::resetGraph(){
	inEdges.clear();
	outEdges.clear();

	for (int i = 0; i < this->numberOfVertices; i++) {
		addVertex();
	}
}

void WeightedGraph::addVertex(){
	vector <int> emptyVector;
	inEdges.push_back(emptyVector);
	outEdges.push_back(emptyVector);
}

void WeightedGraph::addEdge(int sourceVertex, int destVertex, int edgeCost){
	inEdges[destVertex].push_back(sourceVertex);
	outEdges[sourceVertex].push_back(destVertex);
	costEdges[Edge(sourceVertex, destVertex)] = edgeCost;
}

bool WeightedGraph::isEdge(int sourceVertex, int destVertex){
	for (auto iter : inEdges[destVertex]) {
		if (iter == sourceVertex) {
			return true;
		}
	}

	return false;
}

void WeightedGraph::generateRandomGraph(int nrVertices, int nrEdges) {
	if (nrVertices * nrVertices < nrEdges) {
		return;
	}

	this->numberOfVertices = nrVertices;
	this->numberOfEdges = nrEdges;
	this->resetGraph();

	int srcVertex, destVertex, edgeCost;
	int nrExistingEdges = 0;

	while (nrExistingEdges < nrEdges) {
		srcVertex = rand() % nrVertices;
		destVertex = rand() % nrVertices;
		if (this->isEdge(srcVertex, destVertex) == false) {
			edgeCost = rand() % (2 * nrVertices);
			this->addEdge(srcVertex, destVertex, edgeCost);
			nrExistingEdges++;
		}
	}
}

void WeightedGraph::loadGraphFromFile() {
	int sourceVertex, destVertex, edgeCost;

	// we assume the input is valid
	ifstream in(CURRENT_GRAPH_FILE);
	in >> this->numberOfVertices >> this->numberOfEdges;
	this->resetGraph();
	for (int i = 0; i < this->numberOfEdges; i++) {
		in >> sourceVertex >> destVertex >> edgeCost;
		this->addEdge(sourceVertex, destVertex, edgeCost);
	}

	in.close();
}

void WeightedGraph::saveGraphToFile() {
	ofstream out(CURRENT_GRAPH_FILE);
	out << this->numberOfVertices << " " << this->numberOfEdges << "\n";
	for (int srcVertex = 0; srcVertex < this->numberOfVertices; srcVertex++) {
		for (auto destVertex : outEdges[srcVertex]) {
			out << srcVertex << " " << destVertex << " " << costEdges[Edge(srcVertex, destVertex)] << "\n";
		}
	}
	out.close();
}

void WeightedGraph::BFS(int srcVertex, int destVertex) {
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

int WeightedGraph::getDistanceToVertex(int destVertex){
	if (destVertex >= this->numberOfVertices) {
		throw std::exception("Invalid vertex");
	}

	return distanceFromSource[destVertex];
}

std::vector<int> WeightedGraph::getPathToVertex(int srcVertex, int destVertex){
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

void WeightedGraph::pushToStack(int newVertexIndex){
	validNodeStack.push_back(newVertexIndex);
	inStack[newVertexIndex] = true;
}

void WeightedGraph::popFromStack() {
	inStack[validNodeStack.back()] = false;
	validNodeStack.pop_back();
}

std::vector <int> WeightedGraph::newSCC(int SCCRoot) {
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

void WeightedGraph::tarjanDFS(int srcVertex){
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

void WeightedGraph::computeSCC(){
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

int WeightedGraph::getSCCCount(){
	return SCCList.size();
}

std::vector<std::vector<int>> WeightedGraph::getSCCList(){
	return SCCList;
}

WeightedGraph::~WeightedGraph(){
	;
}
