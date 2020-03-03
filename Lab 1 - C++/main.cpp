#include <fstream>
#include <iostream>
#include "weightedGraph.h"
using namespace std;

/*class VectorIterator{
	vector <Node>::iterator head, tail;
	public:
		VectorIterator(vector <Node> v) {
			head = v.begin();
			tail = v.end();
		}

		vector <Node>::iterator operator *() {
			return head;
		}

		VectorIterator operator ++(int) {
			VectorIterator temp = *this;
			head = next(head, 1);
			return temp;
		}

		bool hasEnded() {
			return (head == tail);
		}
};*/

// with cost
void loadGraph(int nrEdges, ifstream &in, WeightedGraph &weightedGraph) {
	int srcVertex;
	int destVertex;
	int cost;

	for (int i = 0; i < nrEdges; i++) {
		in >> srcVertex >> destVertex >> cost;
		weightedGraph.addEdge(srcVertex, destVertex, cost);
	}
}

int main() {
	int nrVertices, nrEdges;
	int command;
	int srcVertex, destVertex, cost;
	ifstream in("graph.txt");

	in >> nrVertices >> nrEdges;
	WeightedGraph weightedGraph(nrVertices);
	{
		cout << "Please insert the command: \n";
		cout << "0. Exit\n";
		cout << "1. Get the number of vertices\n";
		cout << "2. Parse the set of vertices\n";
		cout << "3. Check if the edge exists\n";
		cout << "4. Determine the in/ out degree of a vertex\n";
		cout << "5. Parse the set of inbound edges of a vertex\n";
		cout << "6. Parse the set of outbound edges of a vertex\n";
		cout << "7. Get the endpoints of an edge\n";
		cout << "8. Get the cost of an edge\n";
		cout << "9. Modify the cost of an edge\n";
		cout << "10. Add edge\n";
		cout << "11. Remove edge\n";
		cout << "12. Add vertex\n";
		cout << "13. Remove vertex\n";
		cout << "14. Make a copy of the graph\n";
		cout << "15. Print the graph\n";
		cout << "16. Load the graph from a file\n";
		cout << "17. Save the graph to a file\n";
		cout << "18. Get a randomised graph\n";
	}

	while (true) {
		cout << "Insert command:\n";
		cin >> command;
		try {
			switch (command) {
				case 0:
					cout << "Program has ended\n";
					return 0;

				case 1:
					cout << "Nr of vertices = " << weightedGraph.getNrVertices() << "\n";
					break;

				case 2:
					for (int i = 0; i < weightedGraph.getNrVertices(); i++) {
						cout << i << " ";
					}
					cout << "\n";
					break;

				case 3:
					cout << "Insert srcVertex destVertex:\n";
					cin >> srcVertex >> destVertex;
					if (weightedGraph.isEdge(srcVertex, destVertex)) {
						cout << "The edge exists\n";
					}
					else {
						cout << "The edge doesn't exist\n";
					}
					break;

				case 4:
					cout << "Insert vertex:\n";
					cin >> srcVertex;
					cout << "In degree: " << weightedGraph.getInDegree(srcVertex) << "\n";
					cout << "Out degree: " << weightedGraph.getOutDegree(srcVertex) << "\n";
					break;

				case 5:
					cout << "Insert vertex:\n";
					cin >> srcVertex;
					for (auto iter = weightedGraph.beginInboundEdges(srcVertex); iter != weightedGraph.endInboundEdges(srcVertex); ++iter) {
						cout << iter->index << " ";
					}
					cout << "\n";
					break;

				case 6:
					cout << "Insert vertex:\n";
					cin >> srcVertex;
					for (auto iter = weightedGraph.beginOutboundEdges(srcVertex); iter != weightedGraph.endOutboundEdges(srcVertex); ++iter) {
						cout << iter->index << " ";
					}
					cout << "\n";
					break;

				case 7:
					break;

				case 8:
					cout << "Insert srcVertex destVertex:\n";
					cin >> srcVertex >> destVertex;
					cout << weightedGraph.getEdgeCost(srcVertex, destVertex) << "\n";
					break;

				case 9:
					cout << "Insert srcVertex destVertex newCost:\n";
					cin >> srcVertex >> destVertex >> cost;
					weightedGraph.modifyEdgeCost(srcVertex, destVertex, cost);
					break;

				case 10:
					cout << "Insert srcVertex destVertex cost:\n";
					cin >> srcVertex >> destVertex >> cost;
					weightedGraph.addEdge(srcVertex, destVertex, cost);
					break;

				case 11:
					cout << "Insert srcVertex destVertex\n";
					cin >> srcVertex >> destVertex;
					weightedGraph.removeEdge(srcVertex, destVertex);
					break;

				case 12:
					cout << "Insert srcVertex:\n";
					cin >> srcVertex;
					weightedGraph.addVertex(srcVertex);
					break;

				case 13:
					break;

				case 14:
					break;

				case 15:
					weightedGraph.printGraph();
					break;

				case 16:
					loadGraph(nrEdges, in, weightedGraph);
					break;

				case 17:
					break;

				case 18:
					break;

				default:
					throw 19;
			}
		}
		catch (...) {
			cout << "There has been an error. The operation was not performed\n";
		}
		
	}

	in.close();
	return 0;
}