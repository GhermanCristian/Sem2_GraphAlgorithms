#pragma once
#include <vector>
#include <string>

const int NONEXISTENT_EDGE = 111111111;
typedef std::vector < std::vector <int> > Matrix;

class WeightedGraph{
	private:
		int numberVertices;
		int numberEdges;
		Matrix weights;
		Matrix minimumDistance;
		Matrix aux; // used in multiplications

		void initialiseEmptyGraph();
		void multiplyMatrices(Matrix& first, Matrix& second);
		void displayMatrix(const Matrix& currentMatrix);

	public:
		WeightedGraph(std::string filePath);
		void addEdge(int sourceVertex, int destVertex, int costEdge);
		void computeAPSP();
		int getMinimumDistance(int sourceVertex, int destVertex);
};

