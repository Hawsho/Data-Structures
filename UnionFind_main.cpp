#include"UnionFind.h"
	
	int main(){
	 
	int n;
	int op, x, y;
	cin >> n;
	
	UnionFind *uf = new UnionFind(n);  //Create an UnionFind pointer class Object

	while (cin >> op && cin >> x && cin >> y) // Read three inputs "type integer"
	{
	 
	if (op == -1 && x == -1 && y == -1)   // Exit if statement 
		break;

		if (!op)		// if op = 0
			{
		uf->WQUnion(x,y);	// Call the WQUnion(x,y) Method to connect x & y
				}
			else{

	// else call IsConnected Method, which return T or F depending on wheither they are connected or not
		if (uf->IsConnected(x, y)){	

				cout << "T" << endl;
						}

			else{
				cout << "F" << endl;
				}
					}
	
	}
		uf->~UnionFind();
	return 0;
  };
 
