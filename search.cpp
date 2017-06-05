/*________________________________________________________________
	Author: ISSA G MALKE
	Date: Feb. 25, 2016
	Description: Implementations of bubble, quick, selection, & 
				 inertion Sort Algorithms & Binary Search Algorithm.
________________________________________________________________*/

#ifndef SEARCH_CPP
#define SEARCH_CPP

#include <iostream>
#include <string>
#include <bitset>
#include <typeinfo>
#include <ctime>	//For time
#include <sys/timeb.h>
#include <chrono>	//C++11

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;

template <class T> class search{
	
	public:	
		search();
		~search();
	//Binary Search:
		int rBinary_search(T array[], T data, int low, int high);
		int binary_search(T array[],T data, int low, int high);
		int lOccurenceBS(T array[],T data, int low, int high); //Last Occurence Binary Search.
		
	//Sort Methods:	
		bool bubble_sort(T array[], int v_size);
		bool quick_sort(T *arr, int start, int end);
		bool selection_sort(T *arr, int size);
		bool insertion_sort(T *arr, int size);
		
	//Helper Methods:	
		unsigned long long elapsedTime(uint64_t startTime);
		int partition(T *arr, int start, int end);
		void _print();
		void _print(T array[], int x_size);
		
	private:	
		static const int _size = 25;
		T* _array[_size];
		time_t rawTime;		//Used for Full time stamp w/ Date.
		timeb tb;			//I used it to get time in Milli Seconds.
		uint64_t sTime = 0, eTime = 0;
};

template<class T> search<T>::search(){
	
	for(int i=0; i < _size; ++i){
		_array[i] = new int(i);
	}
}

template<class T> search<T>::~search(){
	
	delete [] _array;
}

template<class T> int search<T>::rBinary_search(T array[], T data, int low, int high){
	
	int midPoint = low + (high - low)/2; //Since (high + low) may overflow the int limit.	
	if( low > high)	return -1;			//Not found!
	
	if(array[midPoint] == data){
		return midPoint;
	}
	else if(array[midPoint] > data){
		binary_search(array, data, low, midPoint-1);
	//	cout << "Call --> binary_search(data, low, midPoint-1) " << low << ", " << midPoint-1 <<endl;
	}
	else{
		binary_search(array, data, midPoint+1, high);
	//	cout << "Call --> binary_search(data, midPoint+1, high) " << midPoint+1 << ", " << high <<endl;
	}
}
template<class T> int search<T>::lOccurenceBS(T array[],T data, int low, int high){
		
	int foundIt = -1;
	while(low <= high){
		int midPoint = low + (high - low)/2;
		
		if(array[midPoint] == data){
			foundIt = midPoint;
	//		cout << midPoint <<endl;
			low = midPoint+1;	//If found it then keep looking towards the right side.
		}
		else if(array[midPoint] > data){
			high = midPoint-1;
		}
		else{
			low = midPoint+1;
		}
	}
	return foundIt;
}
template<class T> int search<T>::binary_search(T array[],T data, int low, int high){
	
		while(low <= high){
			int mid = low + (high - low)/2;	
				
			if(array[mid] == data){
				return mid;
			}
			else if(data > *_array[mid]){
				low = mid+1;
			}
			else{
				high = mid-1;
			}
		}
	return -1;
}
/*================================================================================
									SORT ALGORITHMS
									  Bubble Sort
/=================================================================================*/

template<class T> bool search<T>::bubble_sort(T v[], int v_size){

//	time(&rawTime);	//Record/Take the time @ this moment.
//	cout << ctime(&rawTime)<<endl;

//	ftime(&tb);		//Record/Take the time @ this moment.
//	int nCount = tb.millitm + (tb.time & 0xFFFFF)*1000;	//Return MilliSeconds 
//	cout << nCount <<endl;
sTime =
	std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	bool flag;	//If the Array is already sorted then it will exit the loop.
				//But this can be bad way to check since repeated elements may exits next to each other.
//	int counter = 0;
		for(int i=0; i < v_size-1; ++i){	
			flag = false;
	//		++counter;
			for(int j=0; j < v_size-i-1; ++j){	
		//	++counter;
			//No need to scope over sorted elements.
			//Since for each iteration the last element will be sorted and so on.
			//Since we're gonna access the v[j+1] element then to avoid out of bound exception,
			//we make the iteration goes to v_size-2; which explain why we starting the outer loop fro 1.
				if( v[j] > v[j+1]){
					T temp = v[j];
					v[j] = v[j+1];
					v[j+1] = temp;
					flag = true;
				}
	//		if(flag) break;	
			}
		}
//	cout << counter <<endl;
	cout << "Bubble Sort, MicroSeconds: " << elapsedTime(sTime) <<endl;
	
	return true;
}
/*================================================================================
									SORT ALGORITHMS
									Selection Sort
/=================================================================================*/
template<class T>bool search<T>::selection_sort(T *arr, int size){
	
		for (int i = 0; i < size-1; ++i){
			int mini = i;
			for(int j = i+1; j < size; ++j){
				if(arr[j] < arr[mini]){
					mini = j;
				}
			}
			T temp = arr[i];
			arr[i] = arr[mini];
			arr[mini] = temp;
		}
}
/*================================================================================
									SORT ALGORITHMS
									Insertion Sort
/=================================================================================*/
template <class T> bool search<T>::insertion_sort(T *arr, int size){
	
	for(int i = 1; i < size; ++i){
		
		T value = arr[i];
		int hole = i;
	while(hole > 0 && arr[hole-1] > value){
		arr[hole] = arr[hole-1];
		hole = hole-1;
		}
	arr[hole] = value;
	}
	return true;
}
/*================================================================================
									SORT ALGORITHMS
									  Quick Sort
/=================================================================================*/
template<class T> bool search<T>::quick_sort(T *arr, int start, int end){
	
	if(start > end)	{
//		cout << "\t\tstart: " << start << " end: " << end << " Base Case!" <<endl; 
		return true;	//Base Case
	}
	int partitionIndex = partition(arr, start, end);
//	cout << " Partition Index: " << partitionIndex <<endl;
//	cout << "\tquick_sort(arr,start, partitionIndex-1)" <<endl;
	quick_sort(arr,start, partitionIndex-1);
//	cout << "\tquick_sort(arr,partitionIndex+1, end)" <<endl; //Will be called/print when the previous method
	// is being rolling back when the base case is true.
	quick_sort(arr,partitionIndex+1, end);
	
return true;
}
/*================================================================================
									HELPER METHODS
/=================================================================================*/
template<class T> int search<T>::partition(T *arr, int start, int end){
	
	int partitionIndex = start;
	T pivot = arr[end];
//	cout << "Pivot: " << pivot << " start: " << start <<endl;	//Debugging
	for(int i = start; i < end; ++i){
		if(arr[i] <= pivot){
			T temp = arr[i];
			arr[i] = arr[partitionIndex];
			arr[partitionIndex] = temp;
			++partitionIndex;
		}
	}
		T temp = arr[partitionIndex];
		arr[partitionIndex] = arr[end];
		arr[end] = temp;
		
//	_print(arr,26);			//Debugging 
	return partitionIndex;
}
template <class T> unsigned long long search<T>::elapsedTime(uint64_t startTime){
	
uint64_t currentTime;
currentTime = 
std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
return (currentTime - startTime);	
} 
template <class T> void search<T>::_print(){
	
	for(int i=0; i <_size; ++i){
		cout <<'['<< i << ']'<<"->" << *_array[i] <<" ";
	}
	cout <<endl;
}
template<class T> void search<T>::_print(T x[], int x_size){
	
	for(int i=0; i< x_size; ++i){
		
		cout << x[i] << " ";
	}
	cout <<endl;
}

int main(int argc, char** argv){	
	
	search<int> *s = new search<int>();
//	search<string> *s = new search<string>("isa");
//	s->_print();
	int array[25];
	for(int i=0; i < 25; ++i){
		array[i] = rand()%100;
	}
	cout<<endl;
	s->_print(array,26);
	
//	cout << s->rBinary_search(array,5,0,24)<<endl;
//	cout << s->binary_search(array,5,0,24)<<endl;
//	cout << s->lOccurenceBS(array,5,0,24)<<endl;
//	s->bubble_sort(array,26);
//	s->quick_sort(array,0,25);
//	s->selection_sort(array, 26);
	s->insertion_sort(array, 26);
	s->_print(array,26);	
}
#endif
