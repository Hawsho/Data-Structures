/*
BST : Binary Search Tree
________________________
By ISSA Malke, Aug.17,15
*/
#include "iostream"
#include "iomanip"
#include <cmath>
#include <climits>
#include <queue>

using std::cout;
using std::hex;
using std::endl;
using std::setw;
using std::cin;
using std::max;
using std::queue;

template <class T> class BST{

	private:
		struct Node{
		
			T data;
			Node* left = NULL;
			Node* right = NULL;
		};
	public:
		int count =0;	//Used for Debugging @ find_height() Function.
		Node* root;
		
		BST();
		~BST();
		
		bool search(Node* start, T value);
		void print_Tree();
		void insert_Node(T value);
		T find_mini();
		T find_maxi();

// ================| Tree TRaversal Functions|================	
		void Level_Order_Traversal();
		void Pre_Order_Traversal(Node* root);
		void In_Order_Traversal(Node* root);
		void Post_Order_Traversal(Node* root);

// ================| Is_Binary_Search_Tree |================	
		bool Is_Binary_Search_Tree ();
		bool Is_BST(Node* root, int mini_Value, int max_Value);
	
// =================| Get New Node Function|=================		
		Node* GetNewNode(T value){

			Node* newNode = new Node();
				newNode->data = value;
				newNode->left = NULL;
				newNode->right = NULL;
			return newNode;
		}	
/*
	This is a Recursive Method to add/insert a Node to BST, that it takes "parameters" a node pointer "ROOT" and the value to be added.
	(1) IF the Node pointer doesn't point to anything ===> "it's a leaf" make that pointer points to a new allocated pointer, which the value will add to it,
	    THEN EXIT THE RECURSIVE FUNCTION, returing the address of the new created Node.
	Else, Call the recursive function:
		A__ If the value is greater/larger than current Node's value, then make the current Node points to what the recursive function will return-
		    "Traverse the right side of the Tree, searching for a leaf, once the leaf is found, make it points to a new Node, which will add the value to it & EXIT"  
		B__ Same as (A) but here we are searching for a leaf on the left side of the Tree.

*/
// ==============| Insert Node Helper Method |==============
	Node* insert_Node(Node* ptr, T value){
		
		if(ptr == NULL){	//This is NOT for the Root Node! Since it's being checked earlier.
							//But it's for the new Created Node 
			ptr = GetNewNode(value);
			cout << "\tNew Node Is Created-\n";
 			}	
		else if(value >= ptr->data){

			ptr->right = insert_Node(ptr->right, value);
			}
		else if(value <= ptr->data){

			ptr->left = insert_Node(ptr->left, value);
			}	
		return ptr;
		}
/*
	This Method/Function has a return type of int, and it take a Node pointer as a parameter "the Root".
	It is a Recursive Function, which traverse the two sub-Trees of the Root then add one to the answer of the max function-
	since the root's edge was not counted at the begining. Also, it return -1 if the Tree is empty!
	How it Work?!--------------------------------------------------------------------------------->
		     @ [1] Iteration:
			the Root's address is passed as a parameter to the function, the if statement checks if the Root is pointing to NULL or Not
			if it is then return -1 and Exit!
			Else, the return statement calls the Max function from the standard C++ Library to calculate the Max of the two Sub-Trees, then adds 1.
			In the Max Function:
				First, the RIGHT parameter is Called "find_height(root->left)" which is a Recursive call, so the function will keep call it-self
				till the if statement is true "reaches the last left-most leaf". THen, the Rolling-Back of the Recursive Function is starting from-
				where it stoped at the leaf toward up, AND EVERY TIME IT ROLLING UP ONE NODE THE OTHER PARAMETER OF THE MAX FUNCTION IS CALLED!
				==> Each Node is being searched right & left; left when the recusive function is called, and right when it start rolling-back!			
*/
// ====================| FIND HEIGHT |====================
/*
	This is how it works:
	first, the find_height(root->left); will keep recursively called until the base case is true.
	then the find_height(root->right); will keep recursively called until the base case is true.
	At this point, in this tree example, the left side of the tree consists of: 10->5->4->2->NULL
	so the first recursive function will roll back starting from 2 "the last element", but that after
	the second recursive function is called, and when it is called it will look at the right side of '2'
	which is '3' in our case. Now, when it recursively call again it will have to call the find_height(root->left);
	function first since it is placed first. That will check if there a left Node to the '3' which is not.
	then it will call to check if there is on to the right side of '3' which is also Not; therefore,
	it will roll back to '4' and do the same process. then roll back to '5' and same thing...&etc.
	
	NOTE:
	WHEN A RECURSIVE FUNCTION IS ROLLING BACK IT WILL INCREMENT BY ONE, AND IT DOES NOT GET AFFECTED BY
	THE -1 RETURN FORM THE BASE CASE CONDITION, EXCEPT FOR ONE TIME; THEREFORE, WE ADD ONE @ THE END.
*/
int find_height(Node* root){

	if(root == NULL){//It means it's NOT Allocated/Exist!
					 //<=> the Current Node is a Leaf "has no Childers" or doesn't have left or right child.
		count ++;
		return -1;	//Base Case! It will return -1 at the very last recursive call!
	}
	int left = find_height(root->left);
		cout << "left value " << left <<endl;
		cout << setw(6) << root->data << " ,Base Case# " << count <<endl;
	int right = find_height(root->right);
		cout << "right value " << right <<endl;
		cout << setw(6) << root->data << " ,Base Case# " << count <<endl;
		
	int maxi = max(left,right)+1;
	cout << "\t\t\t" <<left << " " << right <<endl;
// In the max(,) function, it will execute the right parameter first, find_height(root->left)
//	return max(find_height(root->right),find_height(root->left))+1; //+1 for make it even with the -1 
	return maxi;
  }
};
// ====================| CONSTRUCTURE |====================
template <class T> BST<T>::BST():root(NULL){}
// ====================| DESTRUCTURE |====================
template <class T> BST<T>::~BST(){}

// ====================| SEARCH TREE |====================
template <class T> bool BST<T>::search(Node* start, T value){

	if(start == NULL) return false;
		else if(start->data == value) return true;
			else if(value >= start->data) return search(start->right, value);
				else return search(start->left, value);
}
/*
	This Method on the first call "empty Tree" it add a value to he root 'create a Root"
	Then on other calls it call the Recursive function/method to find the leaf location "right || left"
	make it points to the new allocated Node, then add the value to that Node!
*/
// ====================| INSERT NODE |====================
template <class T> void BST<T>:: insert_Node(T value){
		
  Node* ptr = root;
	if(root == NULL){
		root = GetNewNode(value);
		cout << "\t" <<"[+]Root[+] Is Created\n";
		}
	else {
		 insert_Node(ptr, value); //Call Recursive Function
		}
  }
// ====================| FIND MINIMUM |====================
template <class T> T BST<T>::find_mini(){

	Node* track = root;
	if(track == NULL){
		cout << "Tree is Empty!\n";
		return -1;
	}
	while(track->left != NULL){
		track = track->left;
	}
		return track->data;
  }
// ====================| FIND MAXIMUM |====================
template <class T> T BST<T>::find_maxi(){

	Node* track = root;
	if(track == NULL){
		cout << "Tree is Empty!\n";
		return -1;
	}
	while(track->right != NULL){
		track = track->right;
	}
		return track->data;
  }
// ===============| Level_Order_Traversal |===============
template <class T> void BST<T>::Level_Order_Traversal(){

	if(root == NULL) return;
	queue<Node*> Q;
	Q.push(root);
	while( !Q.empty() ){
		Node* curr = Q.front();
		cout << curr->data << " ";
		if(curr->left != NULL ) Q.push(curr->left);
		if(curr->right != NULL ) Q.push(curr->right);
	Q.pop();
     }
}
// ===============| Pre_Order_Traversal |================
/*
-------------------------------------------------------------------
   Time Complexity for All Traversals is O(n); n = # of Nodes
   Space Complexity is propotional to the height of the tree = O(h)
			Worst case = O(n-1) = O(n)
			Best/Average case = O(log n)
-------------------------------------------------------------------
*/
template <class T> void BST<T>::Pre_Order_Traversal(Node* root){

	if(root == NULL) return;
	cout << root->data << " ";
	Pre_Order_Traversal(root->left);
	Pre_Order_Traversal(root->right);
}
// ===============| In_Order_Traversal |================
/*
--------------------------------------------------------------------
 This Traversal will Print the Tree from Mini. to Maxi. in order!!!
---------------------------------------------------------------------
*/
template <class T> void BST<T>::In_Order_Traversal(Node* root){

	if(root == NULL){
//		count ++;
		return;
	}
	In_Order_Traversal(root->left);
	cout << root->data << " ";//" Base Case# " << count << "  ";
	In_Order_Traversal(root->right);
}
// ===============| Post_Order_Traversal |================
template <class T> void BST<T>::Post_Order_Traversal(Node* root){

	if(root == NULL) return;	
	Post_Order_Traversal(root->left);
	Post_Order_Traversal(root->right);
	cout << root->data << " ";
}
// ================| Is_Binary_Search_Tree |================
template <class T> bool BST<T>::Is_BST(Node* root, int mini_Value, int max_Value){

	if(root == NULL) return true;
	
	if(root->data > mini_Value && root->data < max_Value 
		&& Is_BST( root->left, mini_Value, root->data)
		&& Is_BST( root->right, root->data, max_Value))
	  return true;
	else
	  return false;
}
template <class T> bool BST<T>::Is_Binary_Search_Tree (){

	return Is_BST(root, INT_MIN, INT_MAX);
}
// ====================| PRINT TREE |====================
template <class T> void BST<T>::print_Tree(){

	Node* track_left = root;
	Node* track_right = root;
	cout <<endl;
	cout << "--------- TREE-Left-Side ---------\n";
	while(track_left != NULL){	
	cout << "Node's Addr.: " << track_left <<endl;
	cout <<"Node's value: " << track_left->data <<endl;
	cout << "Node->right: " << track_left->right <<endl;
	cout << "Node->left: " << track_left->left <<endl;
	cout << "------------------------\n";
	track_left = track_left->left;
	}
	cout <<endl;
	cout << "--------- TREE-Right-Side ---------\n";
	while(track_right != NULL){	
	cout << "Node's Addr.: " << track_right <<endl;
	cout <<"Node's value: " << track_right->data <<endl;
	cout << "Node->right: " << track_right->right <<endl;
	cout << "Node->left: " << track_right->left <<endl;
	cout << "------------------------\n";
	track_right = track_right->right;
	}
}
// =====================| MAIN() |=====================
int main(){

	BST<int> *class_object = new BST<int>();

	class_object->insert_Node(10);
	class_object->insert_Node(15);
	class_object->insert_Node(5);
	class_object->insert_Node(14);
	class_object->insert_Node(16);	
	class_object->insert_Node(4);
	class_object->insert_Node(6);
	class_object->insert_Node(6);
	class_object->insert_Node(7);	
	class_object->insert_Node(2);	
	class_object->insert_Node(3);
	
	char option;
	while(option != 'Q'){
	cout <<endl;
	cout << "Choose an option from the list below: \n";
	cout << "------------------------------------\n";
	cout << "(A) Insert a new Node  \n";
	cout << "(B) Search for a Node \n";
	cout << "(C) Print the Tree \n";
	cout << "(D) Find the Maxi. element \n";
	cout << "(E) Find the Mini. element \n";	
	cout << "(F) Find the Height of the tree \n";
	cout << "(G) Print a Level Order Traversal of the Tree \n";
	cout << "(H) Print a Pre Order Traversal of the Tree \n";
	cout << "(I) Print a In Order Traversal of the Tree \n";
	cout << "(J) Print a Post Order Traversal of the Tree \n";
	cout << "(K) Is the Tree a Binary Search Tree? \n";
	cout << "(Q) Exit! \n";
	cout << "------------------------------------\n";
	cin >> option;
	if(option == 'B' || option == 'b'){
		cout << "What is the element you're looking for: \n";
		int data;
		cin >> data;
		if(class_object->search(class_object->root, data) == true) cout <<"Found!\n";
		else cout << "Not Found\n";
	  }
	if(option == 'C' || option == 'c') class_object->print_Tree();
	
	if(option == 'E' || option == 'e') cout << "Mini. element in the Tree = " << (class_object->find_mini()) <<endl;
	
	if(option == 'D' || option == 'd') cout << "Maxi. element in the Tree = " << (class_object->find_maxi()) <<endl;

	if(option == 'F' || option == 'f') {
		class_object->count = 0;	//Reset the Debugging Counter. 
		cout << "Height of the Tree = " << (class_object->find_height(class_object->root)) <<endl;
	}

	if(option == 'G' || option == 'g') {
		cout << "Level Order Traversal of the Tree: " <<endl;
		 class_object->Level_Order_Traversal();
	 }
	if(option == 'H' || option == 'h') {
		cout << "Pre Order Traversal of the Tree: " <<endl;
		 class_object->Pre_Order_Traversal(class_object->root);
	 }
	if(option == 'I' || option == 'i') {
		cout << "In Order Traversal of the Tree: " <<endl;
		 class_object->count = 0; //Reset Debugging counter 
		 class_object->In_Order_Traversal(class_object->root);
	 }
	if(option == 'J' || option == 'j') {
		cout << "Post Order Traversal of the Tree: " <<endl;
		 class_object->Post_Order_Traversal(class_object->root);
	 }
	if(option == 'K' || option == 'k') {
		 cout << class_object->Is_Binary_Search_Tree();	
	 }

    }
return 0;
 }	
