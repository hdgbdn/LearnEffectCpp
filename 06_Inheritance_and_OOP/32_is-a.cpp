#include <iostream>
#include <string>
#include <functional>

using namespace std;

class Person{};
class Student : public Person {};

class Bird
{
public:
	virtual void fly() {}
};

class Penguin :public Bird
{

};

class Rectangle
{
public:
	virtual void setHeight(int newHeight) {}
};

class Square : public Rectangle
{
public:
	virtual void setHeight(int newHeight) override {}
};

int main()
{
	// the key point: derived object is a base object, but a base object may not be a derived object
	auto eat = function<void(const Person&)>({ });
	auto study = function<void(const Student&)>({ });
	Person p;
	Student s;
	eat(p);
	eat(s);
	// study(p); // no, person is not student
	study(s);

	// first example is bird and penguin:
	// but due to some language mistake, like we assume birds can fly, but not all birds can fly, like penguin
	// solution 1: delete fly in bird and add a flyingbird class inherits the flyingbird, but if your program and user don't consider the flying problem of birds, you can just
	// keep the fly function, because it may even better.
	//
	// solution 2: in Penguin's overrided fly function, add a runtime error like: Penguin::fly() { error("Attempt to make a penguin fly!"); }
	// pro: don't change the base class. con: the error occurs in runtime;
	// so we can move the detection form runtime to compile time: delete fly function in base and penguin, so when try to penguin.fly(), it can't pass compilation;

	// second example is rectangle and square
	// so should square be derived from rectangle? if so, think about the function setHeight, rectangle can set height and width individually, but square can't

	return 0;
}