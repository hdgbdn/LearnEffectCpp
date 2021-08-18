#include <iostream>
#include <string>

class Person
{
public:
	int age() const { return theAge; }		// it's inline
private:
	int theAge;
};

int main()
{
	// why inline must defined in header file
	// because compiler should know the exact function when try to replace function call with function code
	// c++'s inline occurs during compiling, it means the runtime inline is impossible
	// virtual function ignore inline, because it happens in runtime
	return 0;
}