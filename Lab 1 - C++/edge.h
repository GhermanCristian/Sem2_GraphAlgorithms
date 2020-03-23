#pragma once
using namespace std;

class Edge {
	public:
		int srcVertex;
		int destVertex;

		Edge(int srcVertex, int destVertex);
		bool operator == (const Edge& newEdge) const;
};