#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

class Node {
	public:
		int index = 0;
		int cost = 0;

		Node(int index, int cost) {
			this->index = index;
			this->cost = cost;
		}
};

class Edge {
	public:
		int srcVertex;
		int destVertex;

		Edge(int srcVertex, int destVertex) {
			this->srcVertex = srcVertex;
			this->destVertex = destVertex;
		}

		bool operator == (const Edge &newEdge) const {
			if (this->srcVertex == newEdge.srcVertex)
				return this->destVertex < newEdge.destVertex;
			return this->srcVertex < newEdge.srcVertex;
		}
};

class CustomHashFunction {
	int modulo = 666013; // it is a prime
	public:
		size_t operator()(const Edge& edge) const {
			return (edge.srcVertex * 7 + edge.destVertex * 11) % modulo;
		}
};

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

class Graph {
	private:
		;

	protected:
		int nrVertices;

		vector <vector <Node>> inEdges;
		vector <vector <Node>> outEdges;

		int getEdge(int srcVertex, int destVertex, vector <vector <Node>> v) {
			int position = 0;
			for (auto it = v[srcVertex].begin(); it != v[srcVertex].end(); ++it, ++position) {
				if (it->index == destVertex) {
					return position;
				}
			}
			return -1;
		}

	public:
		// constructor
		Graph(int nrVertices) {
			this->nrVertices = nrVertices;

			vector <Node> emptyVector;

			for (int i = 0; i < nrVertices; i++) {
				inEdges.push_back(emptyVector);
				outEdges.push_back(emptyVector);
			}

			cout << "Done with the graph constructor\n";
		}

		int getNrVertices() {
			return nrVertices;
		}

		bool isEdge(int srcVertex, int destVertex) {
			return (getEdge(srcVertex, destVertex, outEdges) != -1);
		}

		int getInDegree(int vertex) {
			return inEdges[vertex].size();
		}

		int getOutDegree(int vertex) {
			return outEdges[vertex].size();
		}

		auto beginInboundEdges(int vertex) {
			return inEdges[vertex].begin();
			//return VectorIterator(inEdges[vertex]);
		}

		auto endInboundEdges(int vertex) {
			return inEdges[vertex].end();
		}

		auto beginOutboundEdges(int vertex) {
			return outEdges[vertex].begin();
		}

		auto endOutboundEdges(int vertex) {
			return outEdges[vertex].end();
		}

		void addEdge(int srcVertex, int destVertex) {
			if (isEdge(srcVertex, destVertex) == true) {
				throw 1;
			}
			outEdges[srcVertex].push_back(Node(destVertex, 0));
			inEdges[destVertex].push_back(Node(srcVertex, 0));
		}

		void removeEdge(int srcVertex, int destVertex) {
			int inEdgePos = getEdge(destVertex, srcVertex, inEdges);
			int outEdgePos = getEdge(srcVertex, destVertex, outEdges);
			if (inEdgePos == -1 or outEdgePos == -1) {
				throw 1;
			}
			outEdges[srcVertex].erase(outEdges[srcVertex].begin() + outEdgePos);
			inEdges[destVertex].erase(inEdges[destVertex].begin() + inEdgePos);
		}

		void addVertex(int index) {
			;
		}

};

class WeightedGraph : public Graph {
	unordered_map <Edge, int, CustomHashFunction> costEdges;

	public:
		WeightedGraph(int nrVertices) : Graph(nrVertices){
			this->nrVertices = nrVertices;
			cout << "Done with the weighted graph constructor\n";
		}

		int getEdgeCost(int srcVertex, int destVertex) {
			if (getEdge(srcVertex, destVertex, Graph::outEdges) == -1) {
				throw 1;
			}
			return costEdges[Edge(srcVertex, destVertex)];
		}

		void modifyEdgeCost(int srcVertex, int destVertex, int newCost) {
			if (getEdge(srcVertex, destVertex, Graph::outEdges) == -1) {
				throw 1;
			}
			costEdges[Edge(srcVertex, destVertex)] = newCost;
		}

		void addEdge(int srcVertex, int destVertex, int cost) {
			if (isEdge(srcVertex, destVertex) == true) {
				throw 1;
			}
			Graph::outEdges[srcVertex].push_back(Node(destVertex, cost));
			Graph::inEdges[destVertex].push_back(Node(srcVertex, cost));
			costEdges[Edge(srcVertex, destVertex)] = cost;
		}

		void removeEdge(int srcVertex, int destVertex) {
			Graph::removeEdge(srcVertex, destVertex);
			costEdges.erase(Edge(srcVertex, destVertex));
		}

		void printGraph() {
			for (int i = 0; i < nrVertices; i++) {
				cout << i << ": ";
				for(auto it = Graph::outEdges[i].begin(); it != Graph::outEdges[i].end(); ++it){
					cout << it->index << " ";
				}
				cout << "\n";
			}
		}
};

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
					//for (auto iter = weightedGraph.parseInboundEdges(srcVertex); !iter.hasEnded(); iter++)
						//cout << (*iter)->index << " ";
					for (auto iter = weightedGraph.beginInboundEdges(srcVertex); iter != weightedGraph.endInboundEdges(srcVertex); ++iter) {
						cout << iter->index << " ";
					}
					cout << "\n";
					break;

				case 6:
					cout << "Insert vertex:\n";
					cin >> srcVertex;
					//for (auto iter = weightedGraph.parseOutboundEdges(srcVertex); !iter.hasEnded(); iter++)
						//cout << (*iter)->index << " ";
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