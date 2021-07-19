#include <iostream>
#include <string>

class A
{
public:
	~A() { std::cout << "An A obj is deconstructed" << std::endl; }
};

int main()
{
	// the dynamic allocated single object and array have different free method: delete and delete[]
	std::string* stringPtr1 = new std::string;
	std::string* stringPtr2 = new std::string[5];
	
	std::cout << "deleting stringPtr1 using delete[]" << std::endl;
	delete[] stringPtr1;
	std::cout << "deleting stringPtr2 using delete" << std::endl;
	delete stringPtr2;

	// both above have runtime exceptions
	// delete a array or delete[] a object, both a undefined behaviour
	// with vector and string containers, we don't need use array any more(so sort)
	return 0;
}