#pragma once
#include <vector>

using namespace std;

class VectorIterator {
	int currentPos;
	vector <int> iterable;

	public:
		VectorIterator(vector <int> v);
		bool isValid();
		void operator ++();
		int operator *();
};