#include "vectorIterator.h"

VectorIterator::VectorIterator(vector <AdjacentVertex> iterable) {
	currentPos = 0;
	this->iterable = iterable;
}

bool VectorIterator::isValid() {
	return (currentPos < iterable.size());
}

void VectorIterator::operator ++() {
	if (isValid()) {
		currentPos++;
	}
}

AdjacentVertex VectorIterator::operator*() {
	if (!isValid()) {
		throw 1;
	}
	return iterable[currentPos];
}




