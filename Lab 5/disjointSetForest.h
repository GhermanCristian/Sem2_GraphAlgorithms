#pragma once
class DisjointSetForest{
	private:
		int elementCount; // the number of elements in the forest
		int* disjointSetRank;
		int* elementPredecessor;

		bool isRoot(int element);
		/*
			Checks if the current element is the root of its disjoint set
			Input:
				- The element we want to check
			Output:
				- Returns true if the element is the root, false otherwise
		*/
	
	public:
		DisjointSetForest(int elementCount);
		/*
			Constructor
			Input:
				- The number of elements in the forest
			Output:
				- Each disjoint set will have 1 element (the vertex)
		*/

		int findRoot(int element);
		/*
			Finds the root of the disjoint set of a given element
			Input:
				- The element from the disjoint set we search in
			Output:
				- Returns the value of the root
				- Each element on the path from the root to our element will be directly linked to the root
		*/

		void uniteSets(int root1, int root2);
		/*
			Unites two disjoint sets, represented by their roots
			Input:
				- The two roots
			Output:
				- The root with the smaller rank is attached to the other
		*/

		~DisjointSetForest();
		/*
			Destructor
			Input:
				- None
			Output:
				- Destroys the object and deallocates the memory
		*/
};

