#include "disjointSetForest.h"

DisjointSetForest::DisjointSetForest(int elementCount){
	this->elementCount = elementCount;
	this->elementRank = new int[elementCount];
	this->elementPredecessor = new int[elementCount];

	for (int i = 0; i < this->elementCount; i++) {
		this->elementRank[i] = 1;
		this->elementPredecessor[i] = i;
	}
}

bool DisjointSetForest::isRoot(int element){
	return this->elementPredecessor[element] == element;
}

int DisjointSetForest::findRoot(int element){
	int elementCopy = element;
	int root;
	int aux;
	
	while (isRoot(element) == false) {
		element = this->elementPredecessor[element];
	}
	root = element;
	while (isRoot(elementCopy) == false) {
		aux = this->elementPredecessor[elementCopy];
		this->elementPredecessor[elementCopy] = root;
		elementCopy = aux;
	}

	return root;
}

void DisjointSetForest::uniteSets(int root1, int root2){
	if (this->elementRank[root1] > this->elementRank[root2]) {
		this->elementPredecessor[root2] = root1;
	}
	else {
		this->elementPredecessor[root1] = root2;
	}
	if (this->elementRank[root1] == this->elementRank[root2]) {
		this->elementRank[root2] ++; // bc in case of rank equality in that 'else' we attach to r2
	}
}

DisjointSetForest::~DisjointSetForest(){
	delete[] this->elementPredecessor;
	delete[] this->elementRank;
}
