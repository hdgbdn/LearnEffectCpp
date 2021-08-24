#include <iostream>
#include <string>

using namespace std;

class A
{
public:
	A() { cout << "constructed A" << endl; }
	A(const A&) { cout << "copy constructed A" << endl; }
};

class B
{
public:
	B() { cout << "constructed B" << endl; }
	B(const B&) { cout << "copy constructed B" << endl; }
};

class C
{
public:
	C() { cout << "constructed C" << endl; }
	C(const C&) { cout << "copy constructed C" << endl; }
};

class D
{
public:
	D() { cout << "constructed D" << endl; }
	D(const D&) { cout << "copy constructed D" << endl; }
	void test() {}
private:
	A a;
	B b;
	C c;
};

void func1(D d)
{

}

void func2(const D& d)
{

}

//---------------------
class Base
{
public:
	virtual void print() const { cout << "A" << endl; }
};

class Derived : public Base
{
public:
	void print() const override { cout << "B" << endl; }
};

void funcByVal(Base b)
{
	b.print();
}

void funcByRef(const Base& b)
{
	b.print();
}

int main()
{
	// why pass by value costs so much?
	D d;
	cout << "pass by value" << endl;
	func1(d);		// every member of d have been copy constructed	
	cout << "pass by const reference" << endl;
	func2(d);

	// const make sure that user will not change the object

	// reference has polymorphic
	// pass by value causing slicing object, only copy the base part
	{
		Derived d;
		funcByVal(d);
		funcByRef(d);
	}

	// because reference is base on pointer in compiler
	// so for build-in type, pass-by-value if more effective
	// but even your type is small, the copy operation may be very expensive, like copy the object pointed by pointer member
	// and a small type may grow bigger

	// generally, pass value for build-in type, STL iterator and function object, for everything else, use pass by reference to const

	// summary:
	// pass by value if more expensive than by reference because of constructing a new object. add const to make sure the object won't be changed.
	// and only built-in types and some special types designed to be passed by value, otherwise, pass by const reference.
	return 0;
}