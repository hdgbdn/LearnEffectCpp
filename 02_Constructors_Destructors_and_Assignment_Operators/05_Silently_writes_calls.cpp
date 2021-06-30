#include <iostream>
#include <string>

using namespace std;

class Empty
{
};

template <typename T>
class NamedObject1
{
public:
	NamedObject1(const char* name, const T& value);
	NamedObject1(const string& name, const T& value);
	// NamedObject1(); // if declared any constructor, compiler will not synthesize any constructor
private:
	string nameValue;
	T objectValue;
};

template <typename T>
class NamedObject2
{
public:
	NamedObject2(string& name, const T& value);
	// NamedObject1(); // if declared any constructor, compiler will not synthesize any constructor
private:
	string& nameValue;				// will not synthesize copy assignment operator, because reference assignment is meaningless
	const T objectValue;			// also meaningless for const data member
};

class A
{
public:
	A& operator=(const A&) = delete;		// if base class's copy assignment is deleted
};

class B:public A
{
public:
	// copy assignment operator will be also deleted in class B
};

int main()
{
	// class Empty is not empty because compiler will declare:
	// default constructor(if you don't declare any constructor)
	// copy constructor
	// copy assignment operator
	// destructor
	// but it only created when being called

	Empty e1;		// compiler create default constructor and destructor
	Empty e2(e1);	// compiler create copy constructor
	e2 = e1;		// copy assignment operator

	// if you declared any constructor, compiler will not synthesize any constructor
	NamedObject1<int> no1("Smallest Prime Number", 2);
	NamedObject1<int> no2(no1);				// synthesized copy constructor
	// the synthesize copy constructor will call string's copy constructor, and int is a build-in type, so copy int bit-wise

	// synthesized copy constructor will be synthesized only the code will be valid and having meaning
	// see NamedObject2, now constructed by a reference-to-non-const string, and data member nameValue is reference to string
	
	string newDog("Persephone");
	string oldDog("Satch");
	NamedObject2<int> p(newDog, 2);
	NamedObject2<int> s(oldDog, 36);
	// p = s;			// attempt to use deleted function, so compiler delete the copy assignment operator
	// because c++ don't allow change reference, so the copy is meaningless.
	// also for const member
	// and if base class has a inaccessible copy assignment operator, then compiler will not synthesize derived class's copy assignment operator
	B b1, b2;
	// b2 = b1;		// copy assignment operator is also deleted in class B
	
	return 0;
}