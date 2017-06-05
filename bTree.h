/*
=====================
|  B-Tree           |
|  By: ISSA G MALKE |
|  Date: 3/ 12/ 14  |
=====================
*/
#include <string>
#include <sstream>
#include<iostream>

using namespace std;
//using std::string;
//using std::cin;
//using std::cout;
//using std::endl;

static stringstream s;  // Static variable s "keeps the value updated"

struct Key_Node         // the Key_Node Node structure 
{
    string key;		    // The key of the Node, type String
    string Key_Value;  // the Value of the previous Key in the Node
};

//==========================================================================================================================//
//================================== bTree_Node Class Members & Methods Prototypes =========================================//

class bTree_Node	        //First Class bTree_Node
{
public:                     // Public members and functions of the class
    Key_Node* Key;          // Key object type Node, which is defined already
    int degree;		        // Minimum degree (defines the range for number of keys)
    bTree_Node** Child;     // An array of child pointers
    int Number_Of_Keys;     // Number of Keys, integer type
    bool Leaf;		        // Is true when node is leaf. Otherwise false
    bTree_Node(int _degree, bool _leaf_n);                     // Constructor
    ~bTree_Node();			                                  // Destructor
    void Split(int index,bTree_Node* child);                 // Split Method
    void Insert(string key, string Key_Value);              // Insert Method
    void Traversal();	                                   // function to traverse the tree
    bool find(string key, string **Key_Value);            // function to search a key in this tree
    bTree_Node* search(string key, string ***Key_Value); // Search for a Key Method 
    void delete_key(string key);	                    // DElete a Key Method

  // ______________ The following are the helper Methods for the Delete operation _______________\\

    int getKey(string key);	                // Get the key Method/function
    void Remove_Leaf(int index);            // Remove a Leaf Method
    void Remove_Middle_Node(int index);     // Remove Middle Node Method
    string predecessor(int index);	        // gets the predessor of a key
    string successor(int index);	        // get the successor of a key
    void fillIn(int index);	                // FillIN Mthod
    void retrieveFromPrev(int index);       // simillar to the next Method, which is going back
    void GO_Back(int index);	            // Go_Back Method 
    void Connect(int index);	            // Join Method

    // The type of the Class bTree is friend, so its functions and members are accessable without restrictions 
    friend class bTree;		
};

//==========================================================================================================================//
//===================================== bTree Class Members & Methods Prototypes ===========================================//

class bTree
{
private:
    int degree;		       //The degree of the bTree
    bTree_Node *root;     // bTree_Node class object pointer

public: 	             // Public members and functions of the class
    bTree(int size);     // Constructor
    ~bTree();	         // Destructor
    void insert(string key, string Key_Value);	// Insert a Key METHOD
    bool find(string key, string* Key_Value);	// find A Key Method
    bool delete_key(string key);		        // Delete a Key Method
    string toStr();				                // To String Method

  // ______________________ The following is the helper Method ________________________\\

    void Traversal();				// Traversal through the bTree Method
};

//==========================================================================================================================//
//============================================== bTree Class Methods ======================================================//

bTree::bTree(int size)	// Constructor
{
    root = NULL;	// Set the root to NULL 
    degree = size;	// set the DEgree to Size "parameter" 
}
//destructor
bTree::~bTree(){
	delete root;
}
void bTree::insert(string key, string Key_Value) // Insert a Key METHOD
{
    if(root == NULL)	// If the root == NULL then do the following
    {
        root = new bTree_Node(degree,true);     // create a new class object with two parameters (degree, true)
        root->Key[0].key = key;		           // set up the key value at index [0]
        root->Key[0].Key_Value = Key_Value;   // set up the key_value value at index [0]
        root->Number_Of_Keys = 1;	         // set up the Number_Of_Keys to equal 1
    }
    else
    {
        if(root->Number_Of_Keys == 2*degree - 1) // If the degree/number of the Nodes is Maximum
        {
            bTree_Node* Root = new bTree_Node(degree,false); // create a new class object pointer with two parameters (degree, false)
            Root->Child[0] = root;	// set up the child value at index [0]
            Root->Split(0,root);	// set up the split value
	/*
	   compare two keys that the first one is at index [0] if its less then increment the index
	   and insert the new key to the incremented index location/position
	*/
            int index = 0;
            if(Root->Key[0].key < key)
                index++;
            Root->Child[index]->Insert(key,Key_Value);
            root = Root;
        }
        else
        {
            root->Insert(key,Key_Value);
        }
    }
}
	/*
	   Delete a Key Method, which is determine by the inported paramenter key,
	   if its root exit the method; otherwise continue. go to the root->delete_key(key)
	   & create new class pointer object points to root, then if points to leaf then make it points to NULL
	*/
bool bTree::delete_key(string key)
{
        if(!root)
        {
            return false;
        }
	//if the key is not in the bTree
	else if (root->getKey(key) == -1){ 
    	return false;
		}
	else
	{
         root->delete_key(key);
        if(root->Number_Of_Keys == 0)
        {
            bTree_Node *temp = root;
            //if leaf then set root equal to null
            if(root->Leaf)
            {
                root = NULL;
            }
            //if it has a child make 
            else
            {
                root = root->Child[0];
            }
            //old root space freed
            delete temp;
        }
	return true;
  }
}
	/*
	   A Method to find the Key and its Value "key_value" by going to the root and look there
	   if its there then found = true, else false. 
	*/
bool bTree::find(string key, string* Key_Value)
{
    bool found = false;
    if(root->find(key,&Key_Value))
       found = true;
    return found;
}
	/*
	   to String Method, first it calls the TRaversal Method which traverse through the bTree
	   then add the keys together as one string to be return
	*/
string bTree::toStr()
{
    Traversal();
    string x = s.str();
    s.str("");
    return x;
}
	/*
	   The Traversal Method which TRaverse through the bTree, while the root != NULL
	*/
void bTree::Traversal()
{
    if(root != NULL)
        root->Traversal();
}
//==========================================================================================================================//
//====================================== bTree_Node Class Methods ==========================================================//
	/*
	   bTree Node Method, which takes two parameters int degree, and boolean leaf. to creat new node with max capacity of keys
	   that degree = 2*degree -1
	*/
bTree_Node::bTree_Node(int _degree, bool _leaf_n)
{
    degree = _degree;
    Leaf = _leaf_n;
    Key = new Key_Node[2*degree - 1];
    Child = new bTree_Node*[2*degree];
    Number_Of_Keys = 0;
}

bTree_Node::~bTree_Node(){	//destructor to free up memory "Memory Management" 
	delete [] Key;
	delete [] Child;
}

	/*
	   The Traversal Method which TRaverse through the bTree_Node "class", different from the previous TRaversal Method
	   Loop through a loop from 0 to # of keys, and while leaf doesn't point to NULL. Look to its Childs
	*/
void bTree_Node::Traversal()
{
    int i;
    for(i = 0; i < Number_Of_Keys; i++)
    {
        if(!Leaf)
            Child[i]->Traversal();
        s << Key[i].key << "\n";
    }
    if(!Leaf)
        Child[i]->Traversal();
}
	/*
	   Insert a Key with its value Method, if the Leaf doesn't points to NULL, then, while number of keys >= 0
	   shif the keys to the next index "right" and decrement the number of keys variable "i"
	   then inset the new key and its value and increment the number of keys.
	   If the Leaf points to Null, then while previous condition apply, if the child at index [i+1] where i = number of keys
	   equal to maximum "2*degree - 1" then split the node to half and insert the key to the correct splited part of the node
	*/
void bTree_Node::Insert(string key, string Key_Value)
{
    int i = Number_Of_Keys-1;
    if(Leaf)
    {
        while(i >= 0 && Key[i].key > key)
        {
            Key[i+1] = Key[i];
            i--;
        }
        Key[i+1].key = key;
        Key[i+1].Key_Value = Key_Value;
        Number_Of_Keys++;
    }
    else
    {
        while(i >= 0 && Key[i].key > key)
          i++;

          if(Child[i+1]->Number_Of_Keys == 2*degree - 1)
          {
              Split(i+1,Child[i+1]);

              if(Key[i+1].key < key)
                i++;
          }
          Child[i+1]->Insert(key,Key_Value);
    }
}
	/*
	    This is the Split Method which is used previously in the Insert Method, This Method find the middle key in the Node when its Full
	    then split it to two nodes and keep the middle key at the original Node. SO in this case the Node will become three, the original will jsut keep
	    the middle key, and the other two nodes will contain the other keys
	*/
void bTree_Node::Split(int index, bTree_Node* child)
{
    bTree_Node *nNode = new bTree_Node(child->degree,child->Leaf);
    nNode->Number_Of_Keys = degree - 1;

    for(int k = 0; k < degree-1; k++)
        nNode->Key[k] = child->Key[k+degree];

    if(!child->Leaf)
    {
        for(int k = 0; k < degree; k++)
            nNode->Child[k] = child->Child[k+degree];
    }

    child->Number_Of_Keys = degree - 1;

    for(int k = Number_Of_Keys; k >= index+1; k--)
        Child[k+1] = Child[k];

    Child[index+1] = nNode;

    for(int k = Number_Of_Keys-1; k >= index; k--)
        Key[k+1] = Key[k];

    Key[index] = child->Key[degree-1];

    Number_Of_Keys++;
}
	/*
	    find the Key and its Value "Key_Value" Method, this Method takes two parameters Key, and Key_Value
	    this is a Boolean Method, so if the Key is exist return true otherwise return false
	*/
bool bTree_Node::find(string key, string** Key_Value)
{
    if(search(key,&Key_Value) == NULL)
        return false;
    else
    {
        return true;
    }
}
	/*
	    Search for the Key and its Value Method, its search for the key and its value and return it once it found
	*/
bTree_Node* bTree_Node::search(string key, string*** Key_Value)
{
    int i = 0;
    while(i < Number_Of_Keys && key > Key[i].key) //Loop with the condition key > Key[i].key
        i++;

    if(Key[i].key == key)
    {
          ***Key_Value = Key[i].Key_Value;
          return this;
    }

    if(Leaf)	// if the Leaf doesn't points to NULL
        return NULL;

    return Child[i]->search(key,&(*Key_Value));
}
	/*
	    GetKey Method, thsis method return the index of a specific Key that enterend as parameter 
	    the Method goes in a loop and increment the index value while its true then return it at the end of the loop
	*/
int bTree_Node::getKey(string key)
{
    int index = 0;
    while(index < Number_Of_Keys && Key[index].key < key)
    {
        ++index;
    }
    return index;
}
	/*
	     Delete a Key Method, check where the key we need to delete is (is it in this node?)
             calls this function if its a leaf, if not a leaf, calls this function
	     not in the tree if a leaf, check if  the keyis present. if less than minDegree keys, fill up the child,
	     recurisvely called on the index -1 child since last child was merged, if not, call it recursively on the current index child.
	*/
void bTree_Node::delete_key(string key)
{
    int index = getKey(key);
    if(index < Number_Of_Keys && Key[index].key == key)
    {
        if(Leaf)
            Remove_Leaf(index);
        else
            Remove_Middle_Node(index);
    }
    else
    {
        if(Leaf)
            return;
        bool Is_Key_Exist = false;
        if(index == Number_Of_Keys)
            Is_Key_Exist = true;

        if(Child[index]->Number_Of_Keys < degree)
        {
            fillIn(index);
        }

        if(Is_Key_Exist && index > Number_Of_Keys)
            Child[index-1]->delete_key(key);
        else
            Child[index]->delete_key(key);
    }
    return;
}
	/*
	    called by delete to remove from a leaf
	*/
void bTree_Node::Remove_Leaf(int index)
{
    for(int i = index + 1; i < Number_Of_Keys; ++i)
        Key[i-1] = Key[i];
    Number_Of_Keys--;
    return;
}
	/*
	    called by delete to remove from non-leaf
	*/
void bTree_Node::Remove_Middle_Node(int index)
{
    string key = Key[index].key;
	//replace key with pred if the childs predecessor has minDegree keys
    if(Child[index]->Number_Of_Keys >= degree)
    {
        string pred = predecessor(index);
        Key[index].key = pred;
        Child[index]->delete_key(pred);
    }
	//if less than minDegree keys, replace key with the successor
    else if(Child[index+1]->Number_Of_Keys >= degree)
    {
        string check = successor(index);
        Key[index].key = check;
        Child[index+1]->delete_key(check);
    }
	//merge the key with the next child 
    else
    {
        Connect(index);
        Child[index]->delete_key(key);
    }
    return;
}
	/*
	     gets the predessor of a key Method, by doing the following:
	     get to a leaf
	     return leaf's final key
	*/
string bTree_Node::predecessor(int index)
{
    bTree_Node* temp = Child[index];
    while(!temp->Leaf)
        temp = temp->Child[temp->Number_Of_Keys];

    return temp->Key[temp->Number_Of_Keys-1].key;
}
	/*
	     get the successor of akey Method, by doing the following:
	     get the successor of akey
	     go left until we get into a leaf
	     return leaf's first key
	*/
string bTree_Node::successor(int index)
{
    bTree_Node* temp = Child[index+1];
    while(!temp->Leaf)
    {
        temp = temp->Child[0];
    }
    return temp->Key[0].key;
}
	/*
	     this Method fills child Child[index], by doing the following:
	     borrow from child (1 before)
	     borrow from next child
	     merges child [index] with this child's sibiling depending on whether it is the final child (unified with its previous sibling)
  	     or merge it with the next sibling if not the final child
	*/
void bTree_Node::fillIn(int index)
{
    if(index != 0 && Child[index-1]->Number_Of_Keys >= degree)
        retrieveFromPrev(index);

    else if(index != 0 && Child[index + 1]->Number_Of_Keys >= degree)
        GO_Back(index);

    else
    {
        if(index != Number_Of_Keys)
            Connect(index);
        else
            Connect(index - 1);
    }
    return;
}
	/*
	     retrieveFromPrev Method:
	     get a key from the previous child and give it to the current child
	     sibling loses a key while the child gets one
    	     moves the keys in the current child up by one
	*/
void bTree_Node::retrieveFromPrev(int index)
{
    bTree_Node *child = Child[index];
    bTree_Node *sib = Child[index-1];

    for(int i = child->Number_Of_Keys-1; i >= 0; --i)
        child->Key[i+1] = child->Key[i];

    if(!child->Leaf)	//if not a leaf
    {
	//child points go up one
        for(int i = child->Number_Of_Keys; i >= 0; --i)
            child->Child[i+1] = child->Child[i];
    }
    child->Key[0] = Key[index-1];;

    if(!Leaf)	//the childs first key is equal to the current's node keys[index-1]
        child->Child[0] = sib->Child[sib->Number_Of_Keys];

    Key[index - 1] = sib->Key[sib->Number_Of_Keys-1];
    child->Number_Of_Keys = child->Number_Of_Keys + 1;
    sib->Number_Of_Keys = sib->Number_Of_Keys - 1;

    return;
}
	/*
	     THis Method gets key from next and put it in current child
	*/
void bTree_Node::GO_Back(int index)
{
    bTree_Node *child = Child[index];
    bTree_Node *sib = Child[index + 1];
	//put in last key of the current child, the keys[index]
    child->Key[(child->Number_Of_Keys)] = Key[index];
	//1st child of sibling now is last child of child pointer
    if(!child->Leaf)
    {
       child->Child[(child->Number_Of_Keys)+1] = sib->Child[0];
    }

    Key[index] = sib->Key[0];

    for(int i = 1; i < sib->Number_Of_Keys; ++i)
        sib->Key[i-1] = sib->Key[i];

    if(!sib->Leaf)
    {
        for(int i = 1; i < sib->Number_Of_Keys; ++i)
            sib->Child[i-1] = sib->Child[i];
    }
    //add one to the num oof keys of child, while taking away one from the sib 
    //since we are retrieving from next
    child->Number_Of_Keys = child->Number_Of_Keys + 1;
    sib->Number_Of_Keys = sib->Number_Of_Keys - 1;

    return;
}
	/*
	     THis Method puts the current child and next child together, Connect them together
	*/
void bTree_Node::Connect(int index)
{
    bTree_Node *child = Child[index];
    bTree_Node *sib = Child[index + 1];
	//current node fom tree and put key into the child(minDegree-1) position
    child->Key[degree - 1] = Key[index];
	//put keys from the next child to the current child
    for(int i = 0; i < sib->Number_Of_Keys; ++i)
        child->Key[i + degree] = sib->Key[i];

    if(!child->Leaf)
    {
        for(int i = 0; i < sib->Number_Of_Keys; ++i)
            child->Child[i + degree] = sib->Child[i];
    }

    for(int i = index + 1; i < Number_Of_Keys; ++i)
    {
        Key[i-1] = Key[i];
    }

    for(int i = index + 2; i <= Number_Of_Keys; ++i)
        Child[i-1] = Child[i];
	//update node and amount of keys
    child->Number_Of_Keys += sib->Number_Of_Keys+1;
    Number_Of_Keys--;
	//free memory where sibling was located, Memory Management
    delete(sib);
    return;
}
