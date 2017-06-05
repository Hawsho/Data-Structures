/*
Author: Issa G Malke
Date: Feb. 22, 2014
*/
#ifndef TDEQUE_H
#define TDEQUE_H

#include<iostream>
#include<string>
#include<sstream>
#include<new>	//for bad_alloc exception

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::bad_alloc;
using std::stringstream;

//using namespace std;

template <class T>	// Set the Class to be Template Type
class Deque
	{
private:
	// private Data:
	T *deque;		// the array pointer name which will hold the Deque values
	int q_size;		// the Deque size
	int H_count;	// count the number of the header items
	int T_count;	// count the number of the tail items
	int head;		// points to the head
	int tail;		// points to the tail
	int H_start;	// points to the head starting point 
	int T_start;	// points to the tail starting point

public:
	//Constructor
	Deque();

	//Destructor
	~Deque();

	// Inserts the element at the front of the queue. 
	void push_front(T item);
	
	// Inserts the element at the back of the queue
	void push_back(T item);

	// Removes and returns the element at the front of the queue. 
	T pop_front();

	// Removes and returns the element at the back of the queue.
	T pop_back();

	// Returns the number of elements in the queue.
	int size();

	// Tells whether the queue is empty or not.
	bool empty();

	/* Puts the contents of the queue from front to back into a 
	retrun string with each string item followed by a newline
	 */
	string toStr();

	// _______ Helper Method _________

	int findEmptyIndex();	// finding the first empty index 
	void print();			// used just for testing purposes/ printing
	void expand();	 		// exand method to resize the Deque to be double in size
	void shrink();			// shrink method to resize the Deque to be half in size
	int findEmptyIndexII(); // Find empty index to add a tail element
	void check();			// Checks the size of the Deque to determine if it needed to be resized
		
	// ________ Get Methods __________
	int getH_count();
	int getT_count();
	int getQ_size();
	int getH_start();
	int getT_start();
	int getHead();
	int getTail();
	// ________ Set Methods __________
	void setH_count(int h);
	void setQ_size(int x);
	void setTail(int y);
	void setHead(int x);
	void setH_start(int z);
	void setT_start(int z);

};
#endif 

	//Default & Initialize Constructor
	template <class T>
	Deque<T>::Deque():q_size(8),head(0),H_count(0),H_start(-1),tail(getQ_size()-1),T_count(0),T_start(-1) {
		
	// If the memory allocation for the created class object is failed then an Exception is thrown
	try{
		deque = new T[q_size];
		}
	catch (bad_alloc &ex){

	cout << "Memory Allocation Failed!" << endl
		<< "THe Information from the exception object is: "
		<< ex.what() << endl;
	}
 }

	//Destructor
	template <class T>
	Deque<T>::~Deque() {
		delete []deque;
		deque = NULL;
 }

	// Inserts the element at the front of the queue ________________________ push_front _______________________
	/*
		first it checks if the array need to be resized to a bigger size, then it checks if the first index is empty and not a tail
		if so add the first item, which is the head in this case. if the first index if full, then moved to the second one and add the item.
		in both cases increment H_count by one which tracks the number of head items entered.
	*/
	template <class T>
	void Deque<T>::push_front(T item) {

 	//const int Memory = 1;
 //try{
	
	//if(size() == 999) throw(Memory);

	int temp = findEmptyIndex();
	// If the first index[0] is empty and no Head items have been added so far
		//if(IsEmpty(0) && H_start == -1){
		if(getTail() >= 1 && H_start == -1){
			deque[0] = item;
			H_count++;	// an Item is added
			H_start = 0;
	check();	// CHECK for if Resize applies!
				}
	// If there are Head Items starting from >= index[0], and the deque still has empty index(s) left
		else if( H_start >= 0 && H_count >= 1 && getHead() != getQ_size()-1)	{
			deque[head+1] = item;
			head ++;
			H_count++;	// an Item is added
	check();	// CHECK for if Resize applies!
			}
	// If the HEAD is at the end of the deque and there are/ is empty space at the front of the deque, find the
	// first empty index and insert the item there 
		else if( H_start >= 1 && H_count >= 1 && getHead() == getQ_size()-1 )	{
			deque[temp] = item;
			head = temp;
			H_count ++;	// an Item is added
	check();	// CHECK for if Resize applies!
			}
	/* If the first index[0] is Tail, or T_start, find the first empty index to the right of it
	   and add the head there, and initialize it as H_start & Head.
	 */
		else {			
			deque[temp] = item;
			head = temp;
			H_count ++;
			H_start = temp;	
	check();	// CHECK for if Resize applies!
		}
  //}	
 //catch(int caution){
    
       // if(Memory == caution)
        //    cout << "=========================================="<<"\n";
         //   cout << "Caution: You have reached the Memory Limit!" << "\n";
        //    cout << "=========================================="<<"\n";
    	//}	
		
 }
	
	// Inserts the element at the back of the queue ________________________ push_back ________________________
	/*
		first it checks if the array need to be resized to a bigger size, then it checks if the header starting point is larger or equal to zero
		which means that an item is poped from the end of the header group items, which lead to make that position as the new tail position.
		add the item at that position, and increment the number of tail items by one.
		if the first case does not apply, then go to the end of the array, which is the default tail position, and add the item there, also, increment 
		the number of tail items.
		if that position is full, then move to the next position (previous -1) and add the item, also, increment the tail items by one.
	*/
	template <class T>
	void Deque<T>::push_back(T item) {
		
	//const int Memory = 1;
	//try{
	
	//if(size() == 999) throw(Memory);

	int temp = getQ_size()-1;
	int find = findEmptyIndexII();


	// IF the Deque is EMPTY() and want to push_back() for the first time
	if( empty() ){
	
		deque[temp] = item;
		setT_start(temp);
		T_count++;

	check();	// CHECK for if Resize applies!
		}

	// If the items in the array are just added through pushing_back and No push_front is token place.
	// and the end of the array [q_size-1] is empty and a push_back is requested ==> the new item will be pushed to that empty index
	 else if( H_start == -1 && getT_start() <= temp-1 && getTail() == 0){

		deque[getT_start()+1] = item;
		T_start ++;
		T_count++;
	check();	// CHECK for if Resize applies!
	}
	// If no tail items had been added & there are head items, but the index [temp] is free then add the tail item to the [temp] index
	// & set up the (Tail & T_start) to that index
	//else if ( getH_start() >= 0 && IsEmpty(0) && T_start == -1 ){
	else if ( getH_start() >= 0 && getHead() >= getH_start() && T_start == -1 ){
	
		deque[temp] = item;
		T_count++;
		T_start = temp;	
	check();	// CHECK for if Resize applies!	
 	}
	// If no tail items had been added & there are head items, but the index [0] "or higher" is free then add the tail item to the [H_start-1] index
	// & set up the (Tail & T_start) to that index
	//else if ( getH_start() >= 0 && IsEmpty(0) && T_start == -1 ){
	else if ( getH_start() >= 1 && getHead() >= getH_start() && getHead() == temp && T_start == -1 ){
	
		deque[find] = item;
		T_count++;
		setTail(find);
		T_start = find;	
	check();	// CHECK for if Resize applies!	
 	}
	// Else, if the tail position is at index [0] then add the new item to end of the array & update the tail position
	// and keep the T_start position the same!
		//else if( tail == 0 && IsEmpty(temp) )	{
		else if( tail == 0 && getHead() <= temp-1 && getH_start() <= temp-1 && getT_start() <= temp-1){
			tail = temp;
			deque[temp] = item;
			T_count++;	// an Item is added
	check();	// CHECK for if Resize applies!
			}
	// Else, if the end of the array "deque" is empty and the H_start starts from index[0] then add the tail item to the end of the deque
	// and update the T_start position to be the end of the deque, NOTE: the Tail position doesn't need to be updated since its default position
	// is at the end of the deque.

			//else if(IsEmpty(temp) && H_start ==0){
			else if(getHead() <= temp-1 && getHead() >= H_start && H_start ==0 && T_start == -1){
				deque[temp] = item;
				T_count++;	// an Item is added
				T_start = temp;
	check();	// CHECK for if Resize applies!
					}

	// THe same as the previous step but here no head item are exist	
				//else if(IsEmpty(temp) && H_start == -1){
				else if(H_count == 0){
					deque[temp] = item;
					T_count++;	// an Item is added
					T_start = temp;
	check();	// CHECK for if Resize applies!
						}
	// If the deque only has Head items and no Tail items so far
					 else if( getT_start() == -1 ){
						deque[find] = item;
						setT_start(find);
						setTail(find);
						T_count++;
	check();	// CHECK for if Resize applies!
						}
	// ---------------------- After the Deque Expand is token place!
					 else if( getH_start() == 0 && getT_start() == getQ_size()-1 ){
							deque[tail-1] = item;
							tail --;
							T_count++;	// an Item is added
	check();	// CHECK for if Resize applies!
						}						
	// If ALL the previous conditions failed then apply the following:
	// Add the item to the [tail-1] index, decrement the tail position and increment the T_count by one
	// THIS CASE APPLY WHEN HEAD ITEMS ARE POPED_BACK AND AT LEAST ONE TAIL ITEMS EXIST BETWEEN INDEX[0] --> H_START	
						else{
							deque[tail-1] = item;
							tail --;
							T_count++;	// an Item is added
	check();	// CHECK for if Resize applies!
							}
	//		}	
 //catch(int caution){
    
    //    if(Memory == caution)
     //       cout << "=========================================="<<"\n";
     //       cout << "Caution: You have reached the Memory Limit!" << "\n";
      //      cout << "=========================================="<<"\n";
        
    //	}	
 }

	// Removes and returns the element at the front of the queue __________________ POP_FRONT _________________
	/*
		First checks if the number of the elements is < than te size of the arry (deque) if so, shrink it to half.
		Go to the header position and copy it to temporary variable then overwrite it by empty space, decrement the number of header items 
		then decrement the header position by one, then return the poped item.
	*/ 
	template <class T>
	T Deque<T>::pop_front() {
	T temp;
	
	// TRY STATEMENT, if the user trys to pop from an empty array "deque" an exception will be thrown!
  try{		
    
    if(empty()) {
		throw "Error: Cannot pop_front from an empty Queue!";
		}

	if( getH_count() == 1){
		 temp = deque[head];

		//deque[head] = "";
		head = H_start;
		H_count--;
	check();	// CHECK for if Resize applies!
			}

	else if( getH_count() >= 2){
		 temp = deque[head];

		//deque[head] = "";
		head--;
		H_count--;
	check();	// CHECK for if Resize applies!
			}
		else{
			if(getT_count() != 0){
			 temp = deque[tail];

			//deque[tail] = "";
			if ( tail == getQ_size()-1){
				tail = 0;
				}
				else {
					tail ++;
					}	
				T_count--;
	check();	// CHECK for if Resize applies!
				}
			}
	}
 catch(const char aMessage[]){
        
            cout << aMessage << endl;
       	
    	}
	return temp;
 }
	// Removes and returns the element at the back of the queue __________________ POP_BACK __________________

	/*
		First checks if the number of the elements is < than te size of the arry (deque) if so, shrink it to half.
		Second, check if the tail is positioned at the end of the array (deque) or in the begining, doing that by looking at the T_count variable
		that if its value == 0 then add the item at end of the header items group ( circular path) otherwise, add it at the end of the arry following
		the position of the previous tail item.
		in general:
		Go to the tail position and copy it to temporary variable then overwrite it by empty space, decrement the number of tail items 
		then decrement the tail position by one, then return the poped item.
	*/ 
	template <class T>
	T Deque<T>::pop_back() {
	T temp;
	
		// TRY STATEMENT, if the user trys to pop from an empty array "deque" an exception will be thrown!
  try{		
    
    if(empty()) {
	throw "Error: Cannot pop_back from an empty Queue!";
		}

	if ( getH_count() ==0){

		 temp = deque[getT_start()];
		//deque[getT_start()] = "";
		T_start--;
		T_count--;
	check();	// CHECK for if Resize applies!

	}
		else if(getT_count() != 0){
		 temp = deque[tail];

		//deque[tail] = "";
		if ( tail == getQ_size()-1){
			tail = 0;
			}
			else {
				tail ++;
				}	
		T_count--;
	check();	// CHECK for if Resize applies!
	}
		else if(getH_count() >= 0){
 		 temp = deque[getH_start()];

		//deque[getH_start()] = "";
		H_start ++;
		H_count--;	//----------------> Decrement the Head count
		if( getH_count() == 0){
			head = H_start;
			}
	check();	// CHECK for if Resize applies!
	}
 
      }
 catch(const char aMessage[]){
 
            cout << aMessage << endl;
	   
    	}
	return temp;
 }

	// Returns the number of elements in the queue. _________________________ size() __________________________
	/*
	get the number of the items have been added from the head or tail, doing that by combining H_count & T_count
	*/
	template <class T>
	int Deque<T>::size() {

		
		return q_size;
 }

	// _____________________________ Tells whether the queue is empty or not _____________________________
	template <class T>
	bool Deque<T>::empty() {

		if ( H_count >=1 || T_count >= 1)
	
				return false;	
		
			else
				return true;
 }

	/* Puts the contents of the queue from front to back into a ______________ toStr() ______________ PRINT __ PRINT __ PRINT 
	retrun string with each string item followed by a newline
	 */
	template <class T>
	string Deque<T>::toStr() {

		stringstream output;

	if( H_start <= head && H_count >= 1){
			for(int i = getHead(); i >= getH_start(); i--){	
						output << deque[i] << "\n";		
				  	}
				}
		else if( H_start >= head && H_count >= 1){
				
			for(int i = 0; i <= getHead(); i++){	
						output << deque[i] << "\n";
						
				  	}
			for(int i = getQ_size()-1; i >= getH_start(); i--){	
						output << deque[i] << "\n";
						
				  	}
				}
	// -------------------- tail---------------------
		if( T_start >= tail && T_count >= 1 ){
			for(int i = getT_start(); i >= getTail(); i--){	
						output << deque[i] << "\n";
				  	}
				}
		else if( T_start <= tail && T_count >= 1){
	
			for(int i = getT_start(); i >= 0; i--){	
						output << deque[i] << "\n";
				  	}
			for(int i = getQ_size()-1; i >= getTail(); i--){	
						output << deque[i] << "\n";
				  	}
				}
	
		return output.str();
 }

 
	// __________ EXPAND METHOD ___________ EXPAND METHOD ____________ EXPAND METHOD ____________ EXPAND METHOD ____________

 /*
	this method is used to expand the array (deque) size by double, it create a temporary array that holds the orginal array (deque)
	valuse, by going through a loop. then go into two loops, first to copy the header items, then the tail items in one array ( new sized deque)
	TRY STATEMENT FOR THE MEMORY BAD ALLOCATION EXCEPTION
	When creating a new class object “array” in case of expanding “doubling” the current array to 
	the size temp = current array size * 2. The complier will throw an exception in case the memory allocation is failed for the new object.
 */
	template <class T>
	void Deque<T>::expand(){

		int temp = getQ_size();
		int expand = 2*temp;		
	
 try{
		T *exDeque = new T [temp];
	 // COPY the old deque to the new exDeque array
			for(int i=0; i <= temp-1; i++){
				exDeque[i] = deque[i];
					}
	// DELETE the old deque array "call Class Destructor"	
			delete [] deque;
	// Create a new array called deque, with double of the original size
			deque = new T[expand];

		if( H_start <= head && H_count >= 1){
		int x = 0;
			for(int i = getH_start(); i <= getHead(); i++){	
						deque[x] = exDeque[getH_start()+x];
						x++;
				  	}
				setHead (x-1); // or setHead(H_count-1);
				setH_start(0);
				}
			else if( H_start >= head && H_count >= 1){
			int y = 0;	
			for(int i = getH_start(); i <= getQ_size()-1; i++){	
						deque[y] = exDeque[i];
						y++;
				  	}
		 
			for(int i = 0; i <= getHead(); i++){	
						deque[y] = exDeque[i];
						y++;
				  	}
				setHead (y-1);
				setH_start(0);
				}
			else{
				setHead (0);
				}
			if( T_count ==0){
			
				setTail(expand-1);
				setT_start(-1);
			}
	// -------------------- tail---------------------
		if( T_start >= tail && T_count >= 1 ){
		int z = expand-1;
			for(int i = getT_start(); i >= getTail(); i--){	
						deque[z] = exDeque[i];
						z--;
				  	}
				setTail (z+1);
				setT_start(expand-1); 
				}
		else if( T_start <= tail && T_count >= 1){
		int e = expand-1;	
			for(int i = getT_start(); i >= 0; i--){	
						deque[e] = exDeque[i];
						e--;
				  	}
			setT_start(expand-1);

			for(int i = getQ_size()-1; i >= getTail(); i--){	
						deque[e] = exDeque[i];
						e--;
				  	}
				setTail(e+1);
				}
		else {
			setTail(expand-1);
			}		
		if( H_count ==0){
			
				setHead(0);
				setH_start(-1);
			}
	delete [] exDeque;	// DELETE the exDeque array "call Class Destructor", for no need to keep it!
        }
	// Catching the Memory bad allocation exception 
 catch (bad_alloc &ex){

	cout << "Memory Allocation Failed!" << endl
		<< "THe Information from the exception object is: "
		<< ex.what() << endl;
	}

	setQ_size(expand);	// UPDATE the q_size to be the new size "double in size"
 }
 	// __________ SHRINK METHOD ___________ SHRINK METHOD ___________ SHRINK METHOD ___________
	
 /*
	this method is used to shrink the array (deque) size by half, it create a temporary array that holds the orginal array (deque)
	valuse, by going through a loop. then go into a loops to copy the header items and the tail items in one array ( new sized deque)
 */
	template <class T>
	void Deque<T>::shrink(){

		int temp = getQ_size();
		int shrink = (temp/2);		
	
		T *exDeque = new T [temp];
	 // COPY the old deque to the new exDeque array
			for(int i=0; i <= temp-1; i++){
				exDeque[i] = deque[i];
					}
	// DELETE the old deque array "call Class Destructor"	
			delete [] deque;
	// Create a new array called deque, with double of the original size
			deque = new T[shrink];
			
			if( H_start <= head && H_count >= 1){
		int x = 0;
			for(int i = getH_start(); i <= getHead(); i++){	
						deque[x] = exDeque[getH_start()+x];
						x++;
				  	}
				setHead (x-1);
				setH_start(0);
				}
			else if( H_start >= head && H_count >= 1){
			int y = 0;	
			for(int i = getH_start(); i <= getQ_size()-1; i++){	
						deque[y] = exDeque[i];
						y++;
				  	}
		 
			for(int i = 0; i <= getHead(); i++){	
						deque[y] = exDeque[i];
						y++;
				  	}
				setHead (y-1);
				setH_start(0);
				}
			else{
				setHead (0);
				setH_start(-1);
				}
		
			if( T_count ==0){
			
				setTail(shrink-1);
				setT_start(-1);
			}
	// -------------------- tail---------------------
		if( T_start >= tail && T_count >= 1 ){
		int z = shrink-1;
			for(int i = getT_start(); i >= getTail(); i--){	
						deque[z] = exDeque[i];
						z--;
				  	}
				setTail (z+1);
				setT_start(shrink-1); 
				}
		else if( T_start <= tail && T_count >= 1){
		int e = shrink-1;	
			for(int i = getT_start(); i >= 0; i--){	
						deque[e] = exDeque[i];
						e--;
				  	}
			setT_start(shrink-1);

			for(int i = getQ_size()-1; i >= getTail(); i--){	
						deque[e] = exDeque[i];
						e--;
				  	}
				setTail(e+1);
				}
		else {
			setTail(shrink-1);
			setT_start(-1);
			}		
		if( H_count ==0){
			
				setHead(0);
				setH_start(-1);
			}

	delete [] exDeque;	// DELETE the exDeque array "call Class Destructor", for no need to keep it!
	setQ_size(shrink);	// UPDATE the q_size to be the new size "double in size"
 }
// =================================== Helper Method(s) ======================================
 
 /*
	this method finds the first empty index in the array (deque)
 */
	template <class T>	
	int Deque<T>::findEmptyIndex(){

		int find;
			if(T_count == 0 && H_start <= getHead() && H_start >= 1){
				
				find = 0;
			}
			else if(T_count >= 1 && H_start <= getHead() && H_start >= 1 && getTail() != 0){
				
				find = 0;
			}
			else if( T_count >= 1 && H_start >= getHead() ){
				
				find = getHead() +1;
			}
			
		

		return find;
	   
 }
/*
	this method finds the first empty index next to the H_start position in the array (deque)
 */
	template <class T>
	int Deque<T>::findEmptyIndexII(){

		int temp;
		int find = getH_start();

		for(int i=0; i <= getQ_size()-1; i++){
			if( i == find ){
				temp = i-1;
				break;
			   }
			}
		return temp;
	   
 }
	// __________ SIZE CHECK METHOD ___________

/*
	this method is used to check if the Deque needs to be resized every time a pop front/back is called
 */	
	template <class T>
	void Deque<T>::check(){

	// Call the shrink Method if the nmber of the items is less than the 1/4 of the size of the Deque
	if((H_count + T_count) < (size()/4) && size() >= 16){

			shrink();
	    	}

	else if(size() == (H_count + T_count) ){

				expand();
	        }		
 }
	// __________ PRINT METHOD ___________

/*
	this method is used jsut for testing purposes, which prints the array (deque)
 */	
	template <class T>
	void Deque<T>::print(){
	
	cout <<endl;	
	cout << "=========Deque General Print=========" << endl;
	for(int i = 0; i <= getQ_size()-1; i++){
		cout << deque[i] <<endl;
		}
	
 }
	// __________ Get METHOD ___________
	template <class T>
	int Deque<T>::getH_count(){
		
		return H_count;
 }
	
	// __________ Get METHOD ___________
	template <class T>
	int Deque<T>::getHead(){
		
		return head;
 }
	// __________ Get METHOD ___________
	template <class T>
	int Deque<T>::getTail(){

		return tail;
 }	
	// __________ Get METHOD ___________
	template <class T>
	int Deque<T>::getQ_size(){
		
		return q_size;
 }
	// __________ Get METHOD ___________
	template <class T>
	int Deque<T>::getT_count(){

		return T_count;
	}

	// __________ Get METHOD ___________
	template <class T>
	int Deque<T>::getH_start(){

		return H_start;
	}

	// __________ Get METHOD ___________
	template <class T>
	int Deque<T>::getT_start(){

		return T_start;
	}
	// __________ Set METHOD ___________
	template <class T>
	void Deque<T>::setQ_size(int x){
		
		q_size = x;
 }
	// __________ Set METHOD ___________
	template <class T>
	void Deque<T>::setTail(int y){
		
		tail = y;
 }
	// __________ Set METHOD ___________
	template <class T>
	void Deque<T>::setHead(int x){
		
		head = x;
 }

	// __________ Set METHOD ___________
	template <class T>
	void Deque<T>::setH_start(int z){
		
		H_start = z;
 }
	
	// __________ Set METHOD ___________
	template <class T>
	void Deque<T>::setT_start(int z){
		
		T_start = z;
 }

	// __________ Set METHOD ___________
	template <class T>
	void Deque<T>::setH_count(int h){
		
		H_count = h;
 }


