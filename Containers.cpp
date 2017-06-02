/*
Author: Issa G Malke
Date: April, 12, 2017
*/

#include <iostream>
//#include <string>
//#include <sstream>
//#include <stdexcept>
#include <vector>
//#include <iomanip>

// using namespace std;

class Container{

public:
	size_t cSize =0;
	std::vector<int> vecContainer;
	Container();		// Default Constructor
	Container(size_t x=0);	// Init Construtor
	~Container();		// Destructor
	void add_elem(int elem);
	bool insert_elem_at(int elem, int pos);
	void remove_elemAt(int pos);
	bool remove_elem(int elem);
	int get_itr_pos();

private:
	std::vector<int>::iterator itr;

};

Container::Container(size_t x):cSize(x){

	vecContainer.reserve(cSize);
	itr = end(vecContainer);
}

Container::~Container(){}

void Container::add_elem(int elem){

//	int pos = (itr == end(vecContainer)) ? -1 : itr - begin(vecContainer);
//	std::cout << pos <<std::endl;	//Debugging
	vecContainer.push_back(elem);
// Reset the Iterator
//	if(pos == -1) itr = end(vecContainer);
//	else itr = begin(vecContainer) + pos;
}
bool Container::insert_elem_at(int elem, int pos){
	
	vecContainer.insert(begin(vecContainer)+pos,elem);	//Does not change the itr position.
	itr = begin(vecContainer)+pos;						//This One Does!
if(*itr == elem){
	return true;
}
else{
	return false;
}
}
void Container::remove_elemAt(int pos){

	itr = begin(vecContainer) + pos;
	vecContainer.erase(itr);
//	itr = end(vecContainer);
}

bool Container::remove_elem(int elem){

	for(itr = begin(vecContainer); itr !=end(vecContainer); ++itr){

		 if(*itr == elem){

			vecContainer.erase(itr);
		//	itr = end(vecContainer);
			return true;
		}
	}
 return false;
}

int Container::get_itr_pos(){

//	itr = end(vecContainer)-1;
	return *itr;
}
int main(){

//	std::vector<int> vecTwo = {1,2,4,5};
//	std::vector<int> vecThree(5,-1);
	Container f(3);
	std::cout << f.get_itr_pos() << std::endl;
	f.add_elem(1);
	std::cout << f.get_itr_pos() << std::endl;
	f.add_elem(2);
	std::cout << f.get_itr_pos() << std::endl;
	std::cout << f.insert_elem_at(5,2)<<std::endl;
	std::cout << f.get_itr_pos() << std::endl;
	f.add_elem(3);
	std::cout << f.get_itr_pos() << std::endl;
//	std::cout << f.get_itr_pos() << std::endl;
//	vecTwo.insert(begin(vecTwo)+2,3);

//	vecThree.insert(end(vecThree), begin(vecTwo), end(vecTwo));//Add all elements from vecTwo @ end of vecThree
//	vecTwo.insert(begin(vecTwo), 2, 777);
//	f.remove_elemAt(1);
//	std::cout << f.get_itr_pos() << std::endl;
//	f.vecContainer.pop_back();
//	std::cout << f.remove_elem(2) << std::endl;

 	std::cout << "-Sp-\n";
for(int i : f.vecContainer){
	 std::cout << i << std::endl;
 }
 	std::cout << "-Ep-\n";
/*
for(int i : vecTwo){
	 std::cout << i << std::endl;
 }
 	std::cout << "----\n";

for(int i : vecThree){
	 std::cout << i << std::endl;
 }
*/
 return 0;
}


