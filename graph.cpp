/*
	Author: Issa G Malke
	Date: March, 23, 2017
*/

#include <iostream>
#include <list>		//List is like Double Linked-List
#include <memory>	//This header defines general utilities to manage dynamic memory, Smart Ptr

using std::cout;
using std::list;
using std::endl;
using std::cin;
using std::unique_ptr;	//Generic Ptr, Sole owner

class Graph		// This class represents a directed graph using adjacency list representation
{
    private:
        int V; 				// No. of vertices
        list<int> *adj; 		// Pointer to an array containing adjacency lists
    public:
        Graph(int V); 			// Init. Constructor
        void addEdge(int v, int w); 	// function to add an edge to graph
        bool isReachable(int s, int d); // returns true if there is a path from s to d
	void _print();
};
/*
 Create an Array[] of type List<int> allocated in Memory.
 The Array Index is representing a Node/Vertice, and the List<int> "Double linked-list"
 is chaining from each Index representing the Edges, that each Edge Number is a Node NOT
 the weight/Cost of the Edge. In other words, each Array index has its own List<int> that
 Contains the Edges, which represents the connection to other Nodes.
 ==> To ADD a New Node, you fill a new index of the Array "which has fixed size!", but to
 ADD a New Edge, you just expand the List<int> "No fixed Size here!".
 It takes constant time O(1) to Access a Node, but to know its connections, it will need
 to traverse through the List<int> using an Iterator, which it will take O(#of Edges)
 of that specific Node.
*/
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int> [V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

// A BFS based function to check whether (d) is reachable from (s).
bool Graph::isReachable(int str, int des)//str = Start, des = Destination
{
    if (str == des)	return true;	// Base case, Self Loop Node

//  bool *visited = new bool[V];	//Need to be De-allocated; thus, I used smart Ptr
	unique_ptr<bool[]> visited (new bool[V]);

    for (int i = 0; i < V; i++)	// Mark all the vertices as not visited
	{
        	visited[i] = false;
	}
	// Create a queue for BFS
	//This is NOT an Actual Queue, but the List STL provides similar functions.
    list<int> queue;

    visited[str] = true;	// Mark the current node as visited and enqueue it
    queue.push_back(str);
    list<int>::iterator itr;	// it will be used to get all adjacent vertices of a vertex

    while (!queue.empty())
    {
        // Dequeue a Node from queue, and pass it to a Loop to iterate through its Edges.
        str = queue.front();
        queue.pop_front();
    /*
	Get all adjacent vertices/Nodes of the dequeued Node str
        If a adjacent has not been visited, then mark it visited and enqueue it.
	_When the destination Node is Not found inside a List<int> of the Array[str],
	It means the Destination Node is Not directly connected to the Source/Start Node;
	Therefore, we enqueue the Source/Start Node Edges and visit each one of them to check
	if they are connected to the Destination Node. That Explain why we push_back these
	Edges into the Queue, so we can pop_front one by one and check their List<int> through
	a for Loop & an Iterator.
	*/
        for (itr = adj[str].begin(); itr != adj[str].end(); ++itr)
        {
            if (*itr == des)	//If this adjacent node is the destination node, return true.
                return true;

            if (!visited[*itr])	// Else, continue to do BFS.
            {
                visited[*itr] = true;
                queue.push_back(*itr);
            }
        }
    }
    return false;	//Destination Node Not found! Or unreachable from source Node, Return False.
}

void Graph::_print(){

	list<int>::iterator j;
	// Since adj is a pointer to a array type list allocated in Memory
	// ==> to access its size() we use "->". While we use '.' when we are accessing adj[]
	for(int i=0; i <= adj->size()+1; ++i){
		cout << "Node: " << i << " ,Connected to: ";
		for(j = adj[i].begin(); j != adj[i].end(); ++j){

			cout << *j << "->";
		}
	cout <<endl;
	}
}

int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    g._print();

    cout << "Enter the source and destination vertices: (0-3)\n";
    int u, v;
    cin >> u >> v;
    if (g.isReachable(u, v))
        cout << "\nThere is a path from " << u << " to " << v;
    else
        cout << "\nThere is no path from " << u << " to " << v;

// SWAPPING TO SEE IF THERE IS A PATH IN THE OPPOSITE DIRECTION!

    if (g.isReachable(v, u))
        cout << "\nThere is a path from " << v << " to " << u;
    else
        cout << "\nThere is no path from " << v << " to " << u;

    return 0;
}
