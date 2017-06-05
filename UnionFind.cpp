#include"UnionFind.h"


  //______ Default & Initialize Constructor ______//
	UnionFind::UnionFind(int num=0):data(num){

	identifier = new int[num];
	size = new int[num];

	for (int i=1; i<=data; i++){
		identifier[i] = i;
		size[i] = 1;
	    }
	//cout << endl << "Constructor Called" << endl;
      }

  //______Destructor ______//
	UnionFind::~UnionFind(){
	
	delete [] identifier;
	delete [] size;
	identifier = NULL;
	size = NULL;
	//cout << endl << "Destructor Called" << endl;
    }

  //______Find operation ______//
  // Quick find Method that return the index value of the identifier to a specific index "element"
	int UnionFind::Find(int x){

		return identifier[x];	
       	}
  //______Find Tree Root ______//
  /* Separate Method to find the root/parent of an element. Also, finds the Comprasion Path, but it's not used here
	int UnionFind::FindRoot(int i){

		while (i != identifier[i])
			{
		identifier[i] = identifier[identifier[i]];
		i = identifier[i];
	    		}
	return i;
    }
  */
  //______QUnion operation ______//
  /* The Quick Union Method, which Connects two elements if they are NOT connected. 
    This Method does not check for which tree/group is biger that it connects them regradless of their size
   */
	void UnionFind::QUnion(int x, int y){
	
	int tempI = identifier[x];
	
	//cout << "-----> Connect: " << x << " & " << y << " Together";

		if ( Find(x) == Find(y)){
			//cout <<endl << "Oops! Already Connected :)" <<endl;
			return;
			}
		else {

	for (int i=1; i<=data; i++){
				if(identifier[i] == tempI){
				identifier[y] = identifier [i];
						}
			   		 }
			//cout <<endl << "Successfully Connected" <<endl;
		}
	}
	
  //______IsConnected(x, y)? ______//
  // Check if the given two elements are connected or not. Return "T" if true, "F" if false
	bool UnionFind::IsConnected(int x, int y){	
	
	//cout << "Is " << x << " & " << y << " Connected?";
	if ( Find(x) == Find(y)){
		//cout << endl << "T" <<endl;
			return true;
			}
		else {
		//cout << endl << "F" <<endl;
			return false;
			}
	}
  //______Helper Method to print ______//
  // A Helper Method to print the list of the identifier list of the all elements 
	void UnionFind::print(){

	  //cout << endl << "-------------- (" << data << ") -------------" <<endl;
	  for (int i=1; i<=data; i++){
	  cout << identifier[i];
	    }
	cout <<endl;
	 };
 // ___________________ WQUPCfind Method_____________________ //

    int UnionFind::WQUPCfind(int x){
	//while the parent/root is NOT the same as the identifier's index
	while (x != identifier[x]){
	//path compression: make identifier's index equal to the value which it will return => this gets the parent/root of the weighted tree/Group of elements
		identifier[x] = identifier[identifier[x]];
		x = identifier[x];
	}
	return x;
}

// ___________________ WQUnion Method_____________________ //
void UnionFind::WQUnion(int a, int b){

	//cout << "-----> Connect: " << a << " & " << b << " Together";

	int groupI = WQUPCfind(a);	//finds the parent/root of a	
	int groupII = WQUPCfind(b);	//finds the parent/root of b

	//if parents/roots are the same EXIT!
	if (groupI == groupII)
	//cout <<endl << "Oops! Already Connected :)" <<endl;
		return;

	/*if the group/tree size of "a" is greater than the size "y" group/tree. 
	then the new root of the root which contains "y" is now the root of x
	The smaller tree/group must attach to the larger tree/group */

	if (size[groupI] > size[groupII]){
		identifier[groupII] = identifier[a];
		//the new total size of groupI is the original + the connected group size (GroupII)
		size[groupI] += size[groupII];

	}
	/*if the size of the group/tree which contains the root of "b"  is greater than the "a" size => the new "identifier" of the first group is the identifier of "b"
	extand the size of groupII by adding the size of groupI, since is linked to it now */
	else{
		identifier[groupI] = identifier[b];
		size[groupII] += size[groupI];

	}
}











