#pragma once
#include <vector>
#include "node.h"
using namespace std;

class VectorIterator {
	int currentPos;
	vector <Node> iterable;

	public:
		VectorIterator(vector <Node> v);
		bool isValid();
		VectorIterator operator ++(int);
		Node operator *();
};