#include "customHash.h"

size_t CustomHashFunction::operator()(const Edge& edge) const {
	return (edge.srcVertex * 7 + edge.destVertex * 11) % modulo;
	// this will not work quite well with the edges (7, 11) and (11, 7)
}