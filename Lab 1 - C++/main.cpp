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

class LinkedList {
	Node* head;
	int length;

	public:
		LinkedList() {
			head = new Node;
			head = nullptr; // need to differentiate between existing and non existing vertices
			length = 0;
		}

		void addNode(int index) {
			Node* newHead = new Node;
			newHead->index = index;
			newHead->next = head;
			head = newHead;
			length++;
		}

		void addNode(int index, int cost) {
			Node* newHead = new Node;
			newHead->index = index;
			newHead->cost = cost;
			newHead->next = head;
			head = newHead;
			length++;
		}

		void deleteNode(Node* it) {
			Node* prevNode = head;
			length--;

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

		int getLength() {
			return length;
		}

		void copy(const LinkedList &list) {
			head->index = list.head->index;
			head->cost = list.head->cost;
			head->next = list.head->next;
			head = list.head;
		}

		class Iterator {
			Node* nodePtr;

			public:
				Iterator(Node *newNode){
					nodePtr = newNode;
				}

				Node* operator *() const{
					return nodePtr;
				}

				Iterator operator ++(int) {
					Iterator temp = *this;
					nodePtr = nodePtr->next;
					return temp;
				}

				bool hasEnded() {
					return (nodePtr == nullptr);
				}
		};

		Iterator begin() const {
			return Iterator(head);
		}
};

class Graph {
	private:
		int length;

	protected:
		LinkedList* inEdges; // a list of linked lists
		LinkedList* outEdges;
		int nrVertices;

		Node* getEdge(int srcVertex, int destVertex, LinkedList *list) {
			for (auto iter = list[srcVertex].begin(); !iter.hasEnded(); iter++) {
				if ((*iter)->index == destVertex) {
					return *iter;
				}
			}
			return nullptr;
		}

		void increaseListSize(LinkedList *list) {
			LinkedList* temp = new LinkedList[length + 1];
			for (int i = 0; i < length + 1; i++) {
				temp[i].copy(list[i]);
			}

			delete list;
			list = temp;
		}

	public:
		// constructor
		Graph(int nrVertices) {
			inEdges = new LinkedList[nrVertices + 1];
			outEdges = new LinkedList[nrVertices + 1];

			this->nrVertices = nrVertices;
			length = nrVertices + 1;
			cout << "Done with the graph constructor\n";
		}

		int getNrVertices() {
			return nrVertices;
		}

		bool isEdge(int srcVertex, int destVertex) {
			return (getEdge(srcVertex, destVertex, outEdges) != nullptr);
		}

		int getInDegree(int vertex) {
			return inEdges[vertex].getLength();
		}

		int getOutDegree(int vertex) {
			return outEdges[vertex].getLength();
		}

		auto parseInboundEdges(int vertex) {
			return inEdges[vertex].begin();
		}

		auto parseOutboundEdges(int vertex) {
			return outEdges[vertex].begin();
		}

		void addEdge(int srcVertex, int destVertex) {
			if (getEdge(srcVertex, destVertex, outEdges) != nullptr) {
				throw 1;
			}
			outEdges[srcVertex].addNode(destVertex);
			inEdges[destVertex].addNode(srcVertex);
		}

		void removeEdge(int srcVertex, int destVertex) {
			Node* outEdgePtr = getEdge(srcVertex, destVertex, outEdges);
			Node* inEdgePtr = getEdge(destVertex, srcVertex, inEdges);
			if (outEdgePtr == nullptr || inEdgePtr == nullptr) {
				throw 1; // inexistent edge
			}
			outEdges[srcVertex].deleteNode(outEdgePtr);
			inEdges[destVertex].deleteNode(inEdgePtr);
		}

		void addVertex(int index) {
			index++;
			if (index >= length) {
				cout << &(inEdges) << "\n";
				increaseListSize(inEdges);
				increaseListSize(outEdges);
				length *= 2;
			}
			if (index > nrVertices) {
				nrVertices = index;
			}
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
			if (getEdge(srcVertex, destVertex, Graph::outEdges) == nullptr) {
				throw 1;
			}
			return costEdges[Edge(srcVertex, destVertex)];
		}

		void modifyEdgeCost(int srcVertex, int destVertex, int newCost) {
			if (getEdge(srcVertex, destVertex, Graph::outEdges) == nullptr) {
				throw 1;
			}
			costEdges[Edge(srcVertex, destVertex)] = newCost;
		}

		void addEdge(int srcVertex, int destVertex, int cost) {
			Graph::outEdges[srcVertex].addNode(destVertex, cost);
			Graph::inEdges[destVertex].addNode(srcVertex, cost);
			costEdges[Edge(srcVertex, destVertex)] = cost;
		}

		void removeEdge(int srcVertex, int destVertex) {
			Graph::removeEdge(srcVertex, destVertex);
			costEdges.erase(Edge(srcVertex, destVertex));
		}

		void printGraph() {
			for (int i = 0; i < nrVertices; i++) {
				cout << i << ": ";
				for (auto iter = Graph::outEdges[i].begin(); !iter.hasEnded(); iter++)
					cout << (*iter)->index << " ";
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
					for (auto iter = weightedGraph.parseInboundEdges(srcVertex); !iter.hasEnded(); iter++)
						cout << (*iter)->index << " ";
					cout << "\n";
					break;

				case 6:
					cout << "Insert vertex:\n";
					cin >> srcVertex;
					for (auto iter = weightedGraph.parseOutboundEdges(srcVertex); !iter.hasEnded(); iter++)
						cout << (*iter)->index << " ";
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