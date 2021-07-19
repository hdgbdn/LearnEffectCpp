#include <iostream>
#include <string>

using namespace std;

void logCall(const string& info)
{
	cout << info << endl;
}

class Customer
{
public:
	Customer(const string& s): name(s) {};
	string name;
};

class PriorityCustomer: public Customer
{
public:
	PriorityCustomer(const string& s): Customer(s), priority() {}
	PriorityCustomer(const PriorityCustomer&);
	PriorityCustomer& operator=(const PriorityCustomer&);
private:
	int priority;
};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs):Customer(rhs), priority(rhs.priority)
{
	logCall("PriorityCustomer copy constructor");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
	logCall("PriorityCustomer copy assignment operator");
	priority = rhs.priority;
	return *this;
}


int main()
{
	PriorityCustomer pc1("pc1");
	pc1 = PriorityCustomer("pc2");
	// so the 'name' is not copied, can you figure out why? and fix it.

	// Summary
	// In your version's copy operations:
	// 1: copy all the local files
	// 2: copy base part, using base::operator=
	// if you found there is duplicate code in both copy constructor and copy assignment, don't try to call one in other
	// just wrap the same code and put it in a private init function
	logCall(pc1.name);
}