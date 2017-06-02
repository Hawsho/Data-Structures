/*
Author: Issa G Malke
Date: March, 22, 2017
*/

#include "hashTable.h"

hashTable::hashTable(){
	
	size_t _tSize = sizeof(hTable)/sizeof(hTable[0]);
//	cout << "HashTable Array Size\t" <<_tSize <<endl;
	
	for (int i=0; i < _tSize; ++i){		
		hTable[i] = new bucket;
		hTable[i]->name = "empty";
		hTable[i]->age = 0;
		hTable[i]->next = NULL;		
	}
//	cout << "Exiting Default Constructor!\n";
}
hashTable::~hashTable(){}

int hashTable::_hash(const string& name){
	
	int sum = 0;
	for(int i=0; i< name.length(); ++i){
		sum += static_cast<int>(name[i]);
//		cout << name[i] << endl;		//Debugging
	}
//	cout <<sum<<endl;					//Debugging
//	cout << (sum % _tableSize) <<endl;	//Debugging
	return (sum % _tableSize);	//It will return 0 if it's even number, not return a remainder.
}
void hashTable::add_bucket(const string& name, const int& age){
	
	if(find_bucket(name) != "N/A") {	//If the Item/Bucket Already Exist then Out Out Out.
		return;							//To avoid Duplicates!
	}
	int key = _hash(name);
	if(hTable[key]->name == "empty"){
		
		hTable[key]->name = name;
		hTable[key]->age = age;
/*	It's Already pointing to NULL in Constructor.
	Avoid assign it to NULL since it maybe pointing to other Bucket. */
//		hTable[key]->next = NULL;	
	}
	else{
		bucket* temp = hTable[key];
		bucket* newBucket = new bucket;
		newBucket->name = name;
		newBucket->age = age;
		newBucket->next = NULL;
		
		while(temp->next != NULL){		
			temp = temp->next;
		}
		temp->next = newBucket;
	}	
}
string hashTable::find_bucket(const string& name){
	
	string result;
//	stringstream ss;
	int key = _hash(name);
//	ss << key;
//	result = ss.str();
	if(hTable[key]-> name == name){
		
		return (result = to_string(key));	//Uses String Library
	}
	else{
		int counter = 0;
		bucket* tracker = hTable[key];
		while(tracker->next != NULL){
			tracker = tracker->next;
			if(tracker->name == name){
				//This Beautiful thing return a string of two parts: first, the key index
				//second, separated by a '-', is the index "location" of the bucket/item in-
				//the linked list counting from Top where is the Root/Array Index.
				return (result = to_string(key)+"-"+to_string(counter));
			}	
			++counter;
		}
	}
	return "N/A";
}
hashTable::bucket* hashTable::get_bucket(const string& name){
				
		int key = _hash(name);
		bucket* tracker = hTable[key];
		if(tracker->name == name){
			return tracker;
		}
		else{
			while(tracker->next != NULL){
				if(tracker->name == name){
					return tracker;
				}
				tracker = tracker->next;
			}
		}
/*
	If you Don't Allocate the object on the Heap an exception will be thrown.
	If you place the temorary bucket* object at the top under the function declaration-
	the code will compile, but since it's a pointer allocated on the function stack. 
	it will point to other object and overwrite its value! 
*/
	bucket* fakeBucket = new bucket;	
		fakeBucket->name = "None";
		fakeBucket->age = -1;
		fakeBucket->next = NULL;
		
	return fakeBucket;
			fakeBucket = NULL;
			delete fakeBucket;		//DeAllocate the Memory/ Free it Buddy! 
}
bool hashTable::remove_bucket(const string& name){
	
	string location = find_bucket(name);
	if(location == "N/A"){
		return false;
	}	
	else{
		int key = _hash(name);
		if(hTable[key]->name == name){			
			hTable[key]->name = "empty";
			hTable[key]->age = 0;
		}
		else{
			bucket* tracker = hTable[key];
			bucket* temp = hTable[key]->next;	//It will be at least one bucket!
//			cout <<temp->name<<endl;			//Debugging
			do{
				if(temp->name == name){
					tracker->next = temp->next;
					temp = NULL;
					delete temp;
					break;		//If you don't break the compiler will try to access 
								//temp pointer that is deleted!#$%
				} 
				tracker = tracker->next;
				temp = temp->next;
			}
			while(tracker->next != NULL);
		}		
	}
}
bool hashTable::update_bucket(bucket*& uBucket){
	
		int key = _hash(uBucket->name);
		bucket* tracker = hTable[key];
		if(tracker->name == uBucket->name){
			tracker->age = uBucket->age;
			return true;
		}
		else{
			while(tracker->next != NULL){
				if(tracker->name == uBucket->name){
					tracker->age = uBucket->age;
					return true;
				}
				tracker = tracker->next;
			}
		}
	return false;
}
void hashTable::_printTable(){
	 
	for(int i=0; i < _tableSize; ++i){
		cout << i;
		cout <<"\t"<<hTable[i]->name<<endl;
		cout <<"\t"<<hTable[i]->age<<endl;
			if(hTable[i]->next != NULL){
				bucket* tracker = hTable[i];
				while(tracker->next != NULL){
					tracker = tracker->next;
					cout <<"\t\t"<<tracker->name<<endl;
					cout <<"\t\t"<<tracker->age<<endl;
				}
			}
	}	
}