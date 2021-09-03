#include <iostream>
#include <string>

class B
{
public:
	void someFunc() { std::cout << "B::someFunc" << std::endl; }
};

class D: public B
{
public:
	void someFunc() { std::cout << "D::someFunc" << std::endl; }
};

int main()
{
	// let's see if redefine a base non-virtual function
	B b;
	D d;
	B* pb = &d;
	D* pd = &d;

	pb->someFunc();	// "B::someFunc"
	pd->someFunc(); // "D::someFunc"

	// the polymorphic seems wrong, different pointer types call different function;

	// because it breaks the rule that derived classes will inherit the non-virtual function's interface and implementation
}