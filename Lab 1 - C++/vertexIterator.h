#pragma once
#include <vector>

class VertexIterator {
	int currentPos;
public:
	VertexIterator(Graph* currentGraph);
	bool isValid();
	VertexIterator operator++(int);
	int operator *();
};