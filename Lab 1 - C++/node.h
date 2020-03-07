#pragma once
class Node {
	public:
		int index;
		int cost;
		Node(int index, int cost);
		bool operator == (Node newNode) const;
};