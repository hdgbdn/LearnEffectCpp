#include <iostream>
#include <string>

using namespace std;

class B
{
public:
	virtual void funcWithDefault(const string& s = "Base default parameter") = 0;
	void NVI(const string& s = "uniform default parameter") { NVIImplementation(s); }
private:
	virtual void NVIImplementation(const string& s) = 0;
};

class D1: public B
{
public:
	void funcWithDefault(const string& s = "Derived 1 default parameter") override { cout << s << endl; }
private:
	void NVIImplementation(const string& s) override { cout << s << endl; }
};

class D2 : public B
{
public:
	void funcWithDefault(const string& s = "Derived 2 default parameter") override { cout << s << endl; }
private:
	void NVIImplementation(const string& s) override { cout << s << endl; }
};

int main()
{
	D1 d1;
	D2 d2;
	B* pb = &d1;
	cout << "B pointer point to d1" << endl;
	pb->funcWithDefault();
	cout << "B pointer point to d2" << endl;
	pb = &d2;
	pb->funcWithDefault();
	// the default parameter is decided by static type, so a base type pointer's call of function will use the base type's default parameter
	// why? because dynamic bounding parameters costs more than virtual function call

	// what if you want to the virtual function among this inherit system share the same default parameter?
	// first, manually declare the same parameters among all the functions is not a good idea, because it's hard to maintain
	// time to use NVI
	D1* pd1 = &d1;
	cout << "D1 pointer point to d1 call funcWithDefault" << endl;
	pd1->funcWithDefault();
	cout << "D1 pointer point to d1 call NVI" << endl;
	pd1->NVI();
}