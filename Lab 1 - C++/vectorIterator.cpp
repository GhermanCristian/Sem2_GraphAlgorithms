#include "vectorIterator.h"

VectorIterator::VectorIterator(vector <Node> iterable) {
	currentPos = 0;
	this->iterable = iterable;
}

bool VectorIterator::isValid() {
	return (currentPos < iterable.size());
}

VectorIterator VectorIterator::operator ++(int) {
	VectorIterator temporaryIterator = *this;
	if (isValid()) {
		currentPos++;
	}
	return temporaryIterator;
}

Node VectorIterator::operator*() {
	if (!isValid()) {
		throw 1;
	}
	return iterable[currentPos];
}



