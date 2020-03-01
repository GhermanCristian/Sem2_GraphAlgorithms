#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

class Node {
	public:
		int index = 0;
		int cost = 0;

		Node* next = nullptr;
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
			return (edge.srcVertex * 10 + edge.destVertex * 11) % modulo;
		}
};

class Graph {
	private:
		int nrVertices = 0;
	
		void addNodeToList(int srcVertex, int destVertex, Node** list) {
			Node* newHead = new Node;
			newHead->index = destVertex;
			newHead->next = list[srcVertex];
			list[srcVertex] = newHead;
		}

	protected:
		void deleteNode(Node *it, Node *head) {
			Node* prevNode = head;

			if (head == it) {
				// the only node
				if (head->next == nullptr) {
					delete head;
					return;
				}

				head->cost = head->next->cost;
				head->index = head->next->index;
				it = head->next;
				head->next = head->next->next;
				delete it;

				return;
			}

			for (Node* crtNode = head->next; crtNode != nullptr; crtNode = crtNode->next) {
				if (crtNode == it) {
					prevNode->next = it->next;
					delete it;
					return;
				}
			}
		}

	public:
		Node** outEdges;
		Node** inEdges;

		// constructor
		Graph(int nrVertices) {
			outEdges = new Node * [nrVertices + 1];
			inEdges = new Node * [nrVertices + 1];
			for (int i = 0; i < nrVertices + 1; i++) {
				outEdges[i] = inEdges[i] = nullptr;
			}
			this->nrVertices = nrVertices;
			cout << "Done with the graph constructor\n";
		}

		int getNrVertices() {
			return nrVertices;
		}

		Node* isEdge(int srcVertex, int destVertex) {
			for (Node* it = outEdges[srcVertex]; it != nullptr; it = it->next) {
				if (it->index == destVertex) {
					return it;
				}
			}
			return nullptr;
		}

		int getInDegree(int vertex) {
			int degree = 0;
			for (Node* it = inEdges[vertex]; it; it = it->next, degree++);
			return degree;
		}

		int getOutDegree(int vertex) {
			int degree = 0;
			for (Node* it = outEdges[vertex]; it; it = it->next, degree++);
			return degree;
		}

		void addEdge(int srcVertex, int destVertex) {
			if (isEdge(srcVertex, destVertex) != nullptr) {
				throw 1;
			}
			addNodeToList(srcVertex, destVertex, outEdges);
			addNodeToList(destVertex, srcVertex, inEdges);
		}

		void removeEdge(int srcVertex, int destVertex) {
			Node* edgePtr = isEdge(srcVertex, destVertex);
			if (edgePtr == nullptr) {
				throw 1; // inexistent edge
			}
			deleteNode(edgePtr, outEdges[srcVertex]);
		}

};

class WeightedGraph : public Graph {
	void addNodeToList(int srcVertex, int destVertex, int cost, Node** list) {
		Node* newHead = new Node;
		newHead->index = destVertex;
		newHead->cost = cost;
		newHead->next = list[srcVertex];
		list[srcVertex] = newHead;
	}

	int nrVertices;
	unordered_map <Edge, int, CustomHashFunction> costEdges;

	public:
		WeightedGraph(int nrVertices) : Graph(nrVertices){
			this->nrVertices = nrVertices;
			cout << "Done with the weighted graph constructor\n";
		}

		int getEdgeCost(int srcVertex, int destVertex) {
			if (isEdge(srcVertex, destVertex) == nullptr) {
				throw 1;
			}
			return costEdges[Edge(srcVertex, destVertex)];
		}

		void modifyEdgeCost(int srcVertex, int destVertex, int newCost) {
			if (isEdge(srcVertex, destVertex) == nullptr) {
				throw 1;
			}
			costEdges[Edge(srcVertex, destVertex)] = newCost;
		}

		void addEdge(int srcVertex, int destVertex, int cost) {
			addNodeToList(srcVertex, destVertex, cost, Graph::outEdges);
			addNodeToList(destVertex, srcVertex, cost, Graph::inEdges);
			costEdges[Edge(srcVertex, destVertex)] = cost;
		}

		void removeEdge(int srcVertex, int destVertex) {
			Graph::removeEdge(srcVertex, destVertex);
			costEdges.erase(Edge(srcVertex, destVertex));
		}

		void printGraph() {
			for (int i = 0; i < nrVertices; i++) {
				cout << i << ": ";
				for (Node* p = outEdges[i]; p; p = p->next) {
					cout << p->index << " ";
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
					break;
				case 3:
					cout << "Insert srcVertex destVertex:\n";
					cin >> srcVertex >> destVertex;
					if (weightedGraph.isEdge(srcVertex, destVertex) != nullptr) {
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
					break;
				case 6:
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