#include <iostream>
#include <string>

int main()
{
	// main topic: you can declare your own swap function, but it involved in some function namespace trouble

	// first we know, the stl version swap: int temp = a; a = b; b = temp;
	// is not efficiency especially when your have pointer member and your copy assignment is copy the whole pointed data like:
	// *p = *(rhs.p), because just swap the two pointer is ok, so we have to declare our own swap, but there is already a swap in namespace std;
	return 0;
}