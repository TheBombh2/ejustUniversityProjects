//Dijkstra's algorithm for finding shortest path
//the version i did here find the shortest path for source node to every other node
//AND ITS ONLY FOR DIRECTED GRAPHS
//TO ENTER A GRAPH YOU FIRST ADD THE VERTECIES THEN THE EDGES THAT CONNECTS THEM


#include <iostream>
#include <vector>
#include <string>



using namespace std;


struct Node{
	string id;
	float totaldistance;
	//bool visited; //not used until now
	Node* pre;
	Node(string id,float value) {

		this->id = id;
		this->totaldistance = value;
		//this->visited = false;
		this->pre = NULL;
		
	}
};

struct Edge{
	Node* src;
	Node* dist;
	float pathvalue;
	Edge(Node* src,Node* dist,float value) {
		this->src = src;
		this->dist = dist;
		this->pathvalue = value;

	}

	bool areConnected(Node* node1, Node* node2) {
		if (node1 == this->src && node2 == this->dist) return true;
		return false;
	}
};

class Graph{
	vector<Node*> nodes;
	vector<Edge*> edges;

public:

	void addNode(string id,float value = INT_MAX) {
		//ONLY PASS VALUE AS 0 TO BE THE SOURCE NODE
		//IF NOT SOURCE THEN DONT PASS ANYTHING
		Node* temp = new Node(id,value);
		nodes.push_back(temp);
	}

	void addEdge(string src, string dist, float value) {
		Node* t1{ NULL }, * t2{ NULL };
		//search for source node in nodes
		try {
			for (int i = 0; i < nodes.size(); i++) {
				if (nodes[i]->id == src)
					t1 = nodes[i];
			}
		}
		catch(...){
			cout << "Source node wasnt found" << endl;
			return;
		}

		//search for distance node in nodes
		try {
			for (int i = 0; i < nodes.size(); i++) {
				if (nodes[i]->id == dist)
					t2 = nodes[i];
			}
		}
		catch (...) {
			cout << "Distantaion node wasnt found" << endl;
			return;
		}

		//if both are found then add the edge
		Edge* temp = new Edge(t1, t2, value);
		edges.push_back(temp);
	}

	void printEdges() {
		cout << "-----------------------------------------------------------------" << endl;
		for (auto edge : edges) {
			cout << edge->src->id << " -> " << edge->dist->id << " value = " << edge->pathvalue << endl;
		}

		cout << "-----------------------------------------------------------------"<<endl;


		for (auto node : nodes) {
			vector<Node*> adjs = getAdjacentNodes(node);
			cout << "adjs for " << node->id << endl;
			for (auto nod : adjs) {
				cout << nod->id << " ";
			}
			cout << endl;
		}
		cout << "-----------------------------------------------------------------" << endl;
		for (auto node : nodes) {
			cout << "ID: " << node->id<<"\t";
			if (node->totaldistance == INT_MAX) {
				cout << endl << "THERE IS NO PATH FROM SRC TO THIS NODE" << endl;
			}
			else {

				cout << "\nDISTANCE = ";
				if (node->totaldistance == 0) {
					cout << node->totaldistance << "\t";
					cout << node->id;
				}
				else {
					Node* temp = node;
					cout << node->totaldistance << "\t";
					cout << temp->id << " <- ";
					while (temp->pre != NULL) {

						cout << temp->pre->id << " ";
						if (temp->pre->pre != NULL) {
							cout << " <- ";
						}
						temp = temp->pre;

					}

				}
				cout << endl << "---------------------" << endl;
			}
		}
		cout << endl << "-----------------------------------------------------------------" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

	}

	vector<Node*> getAdjacentNodes(Node* node) {
		vector<Node*> adjnodes;
		Node* temp;
		for (auto edge : edges) {
			temp = NULL;
			if (edge->src == node) {
				temp = edge->dist;
			}
			
			if (temp != NULL && !alreadyIn(adjnodes, temp)) {
				adjnodes.push_back(temp);
			}

		}

		return adjnodes;
	}

	bool alreadyIn(vector<Node*> nodes, Node* node) {
		for (auto Tnode : nodes) {
			if (node == Tnode) return true;
		
		}
		return false;
		

	}

	Node* getsmallest(vector<Node*>& nodes) {
		if (nodes.size() == 0) return NULL;
		Node* smallestNode = nodes.front();
		int index = 0;
		for (int i = 1; i < nodes.size();i++) {
			if (nodes[i]->totaldistance < smallestNode->totaldistance) {
				smallestNode = nodes[i];
				index = i;
			}
		}

		nodes.erase(nodes.begin() + index);
		return smallestNode;
	}


	float Distance(Node* node1, Node* node2) {
		for (auto edge : edges) {
			if (edge->areConnected(node1, node2)) {
				return edge->pathvalue;
			}
		}
	}


	void dijkstras() {
		vector<Node*> testnodes;
		testnodes = nodes; //testnodes is a copy of nodes, all the nodes gets modifed here
		// so when we can call them again from og vector
		
		while (!testnodes.empty()) {

			//get smallest Node in distance value
			//after returning it remove it from nodes vecotr
			Node* smallestNode = getsmallest(testnodes);
			for (auto node : testnodes) {
				cout << node->id << " ";
			}
			cout <<" smallest node is "<<smallestNode->id << endl;
			//get adjs for smallest node
			vector<Node*> adjs = getAdjacentNodes(smallestNode);
			
			for (auto adjNode : adjs) {
				float distance = abs(Distance(smallestNode, adjNode) + smallestNode->totaldistance); //used abs() here 
																								   //because INT_MAX - 25 = -INT_MAX
																								   // and since -INT_MAX < INT_MAX
																								   //it ruined it
				if (distance < adjNode->totaldistance) {
					adjNode->totaldistance = distance;
					adjNode->pre = smallestNode;
				}
			}

		}
	}
	




};


int main() {

	Graph g1;
	//when we pass 0 when adding a node then this node is the source
	//calculate the distance from the source to every node
	g1.addNode("A",0);
	g1.addNode("B");
	g1.addNode("C");
	g1.addNode("D");
	g1.addNode("E");
	g1.addNode("F");

	g1.addEdge("A", "B", 50);
	g1.addEdge("A", "C", 45);
	g1.addEdge("A", "D", 10);
	g1.addEdge("B", "C", 10);
	g1.addEdge("B", "D", 15);
	g1.addEdge("C", "E", 30);
	g1.addEdge("D", "A", 10);
	g1.addEdge("D", "E", 15);
	g1.addEdge("E", "B", 20);
	g1.addEdge("E", "C", 35);
	g1.addEdge("F", "E", 3);
	g1.dijkstras();
	g1.printEdges();

	Graph g2;
	g2.addNode("A", 0);
	g2.addNode("B");
	g2.addNode("C");
	g2.addNode("D");
	g2.addNode("E");
	g2.addNode("F");

	g2.addEdge("A", "B", 5);
	g2.addEdge("A", "C", 12);
	g2.addEdge("B", "A", 3);
	g2.addEdge("B", "C", 9);
	g2.addEdge("C", "D", 20);
	g2.addEdge("C", "E", 50);
	g2.addEdge("D", "C", 18);
	g2.addEdge("D", "F", 8);
	g2.addEdge("E", "C", 42);
	g2.addEdge("E", "F", 6);
	g2.addEdge("F", "E", 6);
	g2.dijkstras();
	g2.printEdges();


	Graph g3;
	g3.addNode("SUMED");
	g3.addNode("SEVEN_SKY_INDUSTRY");
	g3.addNode("EJUST");
	g3.addNode("EJUST_SQUARE");
	g3.addNode("BORG_ELARAB_TECH_UNI",0);
	g3.addNode("RESEARCH_CITY");
	g3.addNode("HQ");
	g3.addNode("ALEX_STEM");
	g3.addNode("ELSALAM_HOSPITAL");

	g3.addEdge("SUMED", "EJUST", 2);
	g3.addEdge("SUMED", "SEVEN_SKY_INDUSTRY", 5.1);
	g3.addEdge("SEVEN_SKY_INDUSTRY", "SUMED", 5.1);
	g3.addEdge("SEVEN_SKY_INDUSTRY", "EJUST", 4.2);
	g3.addEdge("EJUST", "SEVEN_SKY_INDUSTRY", 4.2);
	g3.addEdge("EJUST", "SUMED", 2);
	g3.addEdge("EJUST", "EJUST_SQUARE", 1);
	g3.addEdge("EJUST_SQUARE", "EJUST", 1);
	g3.addEdge("EJUST_SQUARE", "BORG_ELARAB_TECH_UNI", 1);
	g3.addEdge("EJUST_SQUARE", "RESEARCH_CITY", 1.8);
	g3.addEdge("BORG_ELARAB_TECH_UNI", "EJUST_SQUARE", 1);
	g3.addEdge("RESEARCH_CITY", "EJUST_SQUARE", 1.8);
	g3.addEdge("RESEARCH_CITY", "ELSALAM_HOSPITAL", 2.8);
	g3.addEdge("RESEARCH_CITY", "HQ", 1.4);
	g3.addEdge("ELSALAM_HOSPITAL", "RESEARCH_CITY", 2.8);
	g3.addEdge("ELSALAM_HOSPITAL", "HQ", 2.7);
	g3.addEdge("ELSALAM_HOSPITAL", "ALEX_STEM", 2.3);
	g3.addEdge("HQ", "RESEARCH_CITY", 1.4);
	g3.addEdge("HQ", "ELSALAM_HOSPITAL", 2.7);
	g3.addEdge("HQ", "ALEX_STEM",1);
	g3.addEdge("ALEX_STEM", "ELSALAM_HOSPITAL", 2.3);
	g3.addEdge("ALEX_STEM", "HQ", 1);

	g3.dijkstras();
	g3.printEdges();

}