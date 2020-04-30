#pragma once
class DisjointSetForest{
	private:
		int elementCount;
		int* elementRank; 
		int* elementPredecessor;

		bool isRoot(int element);
	
	public:
		DisjointSetForest(int elementCount);
		int findRoot(int element);
		void uniteSets(int root1, int root2);
		~DisjointSetForest();
};

