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

	// but due to some language mistake, like we assume birds can fly, but not all birds can fly, like penguin
	// so whether
	return 0;
}