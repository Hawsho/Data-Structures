/*

 SSL : SINGLE LINKED LIST 
_________________________
By ISSA Gabriel Malke
    Aug. 16, 2015

KEEP IN MIND:
	
*** WHEN YOU MAKE HEAD OR TAIL OR ANY NODE = "EQUAL TO" NODE  <==>  THAT MEAN IT POINTING TO IT, & HAS ITS ADDRESS

	THEREFORE, WHEN YOU MAKE newNODE = HEAD, IT MEANS THAT newNODE POINTS TO THE NODE, WHICH THE HEAD IS POINTING TO!
	ALSO, WHEN YOU WRITE: HEAD = someNODE  ,THEN when you write:  HEAD->NEXT = otherNODE  "its equivlant to" <==> someNODE->NEXT = otherNODE
	IN OTHER WORDS, YOU ARE MODIFYING THE someNODE

***	NODE->NEXT = NODE
- THE LEFT SIDE IS ACCESSING THE PARAMETER OF THE NODE "NEXT" AND MAKE IT POINT TO NODE'S ADDRESS THAT IS ON THE RIGHT SIDE.

***	NODE->NEXT = NODE->NEXT;
- THE LEFT SIDE IS ACCESSING THE PARAMETER OF THE NODE "NEXT" AND MAKE IT POINT TO THE WHAT THE NODE ON THE RIGHT SIDE POINTING TO "NEXT NODE"

================================================================================================
= Head & Tail are Node Pointers, that when we make a Head = Temp "Any Created Node Pointer"    =
= That means that the Head pointer has the same address of the created Node pointer ==>        =
= That when we type Head->next that mean we are accessing the Created Node Pointer's next      =
= parameter and make it linked to something "another Node"                                     =
================================================================================================

*/

#include "iostream"
#include "iomanip"

using std::endl;
using std::cout;
using std::cin;
using std::setw;

template <class T>

class SLL{

  private:
	
	struct Node {
		T data;
		Node* next;
	};

	//Node* head;
	Node* tail;
	
  public:
		Node* head;	

		SLL();
		~SLL();
		void insertNode(T value); //Insert @ the end of the LInked LIst
		void insertAt(T value, int n); // Insert @ specific position "n"
		void Delete(int n);  // Delete a Specific Node
		void printNode();
		void RecursivePrint(Node* begin);
		void Reverse();
		void Recursive_Reverse(Node* begin);
};

template <class T>
SLL<T>::SLL():head(NULL),tail(NULL){
    
}

template <class T>
SLL<T>::~SLL(){
}

template <class T>
void SLL<T>::insertNode(T value){

  Node* temp = new Node();

  if(head == NULL){
	
	temp -> data = value;
	temp -> next = NULL;
  	head = temp;  
	tail = temp;
 }
  else{
	temp->data = value;
  /*
	temp->next = head "mean" Link the Temp Node to the Node, which the head is pointing to!
	head = temp "mean" that make the head points "Contain the address of new Node" to the new Node 
*/
	temp->next = head; 
	head = temp;
  }			
}

template <class T> void SLL<T>::insertAt( T value, int position){
	
	Node* temp = new Node();
	Node* track = head;

	 temp->data = value;

	  for(int i=0; i < position-2 ;i++){
	  	
		track = track->next;
	  }
	  
	temp->next = track->next;
	track->next = temp;
 }
template <class T> void SLL<T>::Delete(int position){

	Node* track_prev = head;
	
	for(int i=0; i < position-2; i++){ //if you make it == position-1 it will not work properly!!

		track_prev = track_prev->next;
	 }
	Node* track_curr = track_prev->next;
	track_prev->next = track_curr->next;
	delete (track_curr);
 }

template <class T> void SLL<T>::printNode(){

	Node* track = head;
	cout <<endl;
	while (track != NULL){
	  cout << setw(6) <<track->data;
	  track = track->next;
	}
	cout <<endl<<endl;
}
// You should pass the head Node to print the list from the head to the end, where it points to NULL
template <class T> void SLL<T>::RecursivePrint(Node* start){
	
	if(start == NULL){ // If you type start->next instead, the program will not PRINT the last node because-
			   // it will jump to excute the line after the Recurssive call!, so it will miss the print statement!	
	cout <<endl; 	   //Prints new line before exits, useful for the printing purposes
		return;
	 }
	  cout << setw(6) << start->data;      //Prints the Linked List in the Default order 
		RecursivePrint(start->next);
	//cout << setw(6) << start->data;	//This will print the Linked List in Reverse Order!
 }
template <class T> void SLL<T>::Recursive_Reverse(Node* start){

  // Once the function reaches the last Node that points to NULL
  // Make head points to that Node, then jump to the line after the Recursive function call
	if(start->next == NULL){
		head = start;
		return;
	}	  
	  Recursive_Reverse(start->next);
  /*
        When the start Node is @ the end of the Linked List, the following will excuted:
	1) Create a temporary "local" Node that points to current "start" Node ->next
	2) Make the temp Node points to start Node, which is changing every time the Recursive function is Rolling back!
	3) Make the start Node points to NULL.
	-------------------------------------------------------------------------------
	>> First Rolling-back of the Recursive function, the following senario will happen:
	- the head Node will be already pointing to the end of the list, that this will take place within the if() statement
	- a Temporary Node will be created to points to NULL, since the start->next points to NULL.
	- Then this Temporary Node "->next" will point to the last Node in the list, where the first Rolloing-back is happening
	- Then the last Node in the list will point to NULL, "it was already, but this not the case when Rolling-back continues"
	-------------------------------------------------------------------------------
	>> Second Rolling-back:
	- the Temporary Node will be pointing to the last Node in the List.
	- Make the Last Node change its pointing from NULL to point to the current Node in the Roll-back "previous Node = Node before the last"
	- Make the previous Node "Current Node in the Roll-back" points to NULL.
  */
	  Node* temp = start->next;
	  temp->next = start;
	  start->next = NULL;	  
 }
template <class T> void SLL<T>::Reverse(){

	tail = head;  //Update the Tail pointer
	Node* curr = head;
	Node* next = NULL;
	Node* prev = NULL;
  while(curr != NULL){
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next; /* Since the curr->next is pointing to previous Node
                    If we don't do this step, Curr will point to NULL
  		    Also, this step replace the Default step of traversing by using 
		    curr = curr->next;
		  */
  }
  head = prev;	// Update the Head pointer
}

int main(){

  SLL<int> *Node = new SLL<int>();

  Node->insertNode(1);
  Node->insertNode(2);
  Node->insertNode(3);
  Node->insertNode(4);
  Node->insertNode(5);
  Node->insertNode(6);

 // Node->Reverse();
 // Node->insertAt(9, 3);
 // Node->Delete(2);
  Node->printNode();
  cout<<endl;
  Node->Recursive_Reverse(Node->head);
  Node->printNode();
 // Node->RecursivePrint(Node->head); //We cannot access head if its a private
  //insertNode(float 1.1);


return 0;
}
