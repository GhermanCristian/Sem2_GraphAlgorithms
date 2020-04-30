#include "customHash.h"

size_t CustomHashFunction::operator()(const Edge& edge) const {
	return (edge.srcVertex * 7 + edge.destVertex * 11) % modulo;
}