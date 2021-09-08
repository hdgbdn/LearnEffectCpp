#include <iostream>
#include <string>

class Person{};

class Student : private Person{};

void eat(const Person&) {}

class Timer
{
public:
	virtual void onTick() { }
};

int main()
{
	// private inheritance is not "is-a"
	Person p;
	Student s;
	eat(p);
	//eat(s);		// conversation to inaccessible base: Person is not allowed
	// so, what does a private inheritance mean?
	// it means implemented-in-terms-of, like composition, means a part of derived class's implementation is based on base class
	// don't mean that B and D has some concept relation

	// example: we want a widget to have timer's function
	// first, try to private inherit 

	return 0;
}