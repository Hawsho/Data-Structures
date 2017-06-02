/*

 DLL : DOUBLED LINKED LIST 
_________________________
By ISSA Gabriel Malke
    Aug. 5, 2015
*/
#ifndef DLL_CPP
#define DLL_CPP

#include <iostream>
#include <iomanip>
//using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::setw;

template <class T> class DLL {

private:
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};
public:
	Node* head;
	Node* tail;
	DLL();
	~DLL();
	void insert_node(T value);
	void insert_node_at(T value, int position);
	void print_from_head();
	void print_from_tail();
};

template <class T> DLL<T>::DLL() :head(NULL), tail(NULL) {}

template <class T> DLL<T>::~DLL() {
	head = NULL;	delete head;
	tail = NULL;	delete tail;

}
template <class T> void DLL<T>::insert_node(T value) {

	Node* node = new Node();
	if (head == NULL) {
//		cout << "Node_Data: ";
		node->data = value;
//		cout << node->data << " | ";
//		cout << "Node_Addr: " << node << "  ";
		node->next = NULL;
//		cout << "Next-> " << node->next << "  ";
		node->prev = NULL;
//		cout << "Prev-> " << node->prev << "  ";
		head = node;
//		cout << "Head-> " << head << "  ";
		tail = node;
//		cout << "Tail-> " << tail << endl;
	}
	else {
//		cout << "Node_Data: ";
		node->data = value;
//		cout << node->data << " | ";
//		cout << "Node_Addr: " << node << " | ";
		node->next = head;
//		cout << "Next-> " << node->next << " | ";
		node->prev = NULL;
//		cout << "Prev-> " << node->prev << " | ";
		head->prev = node; //Since head = Node,then head->prev = Node->prev. Link the previous Node with the new added Node.
//		cout <<"prev_Node_Addr: " << head << " | ";
//		cout << "prev_Node->prev " << head->prev << " | ";
		head = node;
//		cout << "Head "<< head << endl;
	}
}
template <class T> void DLL<T>::insert_node_at(T value, int position){

	if (position == 1) { insert_node(value); }
else {

	Node* newNode = new Node();
	Node* track = head;
	for (int i = 0; i < position - 2; i++) {

		track = track->next;
	}
	newNode->data = value;		// Assign a value to the new Node
	newNode->next = track->next;//Link the new Node to the NEXT Node, "track->next : gives the Address of the next NODE"
	newNode->prev = track;		// Link the new Node to the current NODE
	track->next->prev = newNode;//Link the next Node's prev parameter to the new Node
	track->next = newNode;		// Link the current Node to the new Node
	}
}
template <class T> void DLL<T>::print_from_tail() {

	Node* track = tail;
	while (track != NULL) {
		cout << setw(6) << track->data;
		track = track->prev;
	}
	cout << endl;
}
template <class T> void DLL<T>::print_from_head() {

	Node* track = head;
	while (track != NULL) {
		cout << setw(6) << track->data;
		track = track->next;
	}
	cout << endl;
}
#endif // !DLL_CLASS
