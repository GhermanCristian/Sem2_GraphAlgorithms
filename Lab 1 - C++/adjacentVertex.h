#pragma once
class AdjacentVertex {
	public:
		int index;
		int cost;
		AdjacentVertex(int index, int cost);
		bool operator == (AdjacentVertex newAdjacentVertex) const;
};