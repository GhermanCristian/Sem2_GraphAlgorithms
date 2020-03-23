#pragma once
#include <vector>
#include "adjacentVertex.h"
using namespace std;

class VectorIterator {
	int currentPos;
	vector <AdjacentVertex> iterable;

	public:
		VectorIterator(vector <AdjacentVertex> v);
		bool isValid();
		void operator ++();
		AdjacentVertex operator *();
};