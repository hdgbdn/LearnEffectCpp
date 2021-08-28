#include <iostream>
#include <string>

using namespace std;

class Base
{
public:
	virtual void mf1() = 0;
	virtual void mf1(double x) { cout << "Base::mf1(double x)" << endl; };
	virtual void mf2() { cout << "Base::mf2()" << endl; }
	virtual void mf2(double x) { cout << "Base::mf2(double)" << endl; }
	void mf3(double) { cout << "Base::mf3(double)" << endl; }
};

class Derived : public Base
{
public:
	virtual void mf1()  { cout << "Dervied::mf1()" << endl; }
	void mf3() { cout << "Dervied::mf3()" << endl; }
};

class NewDerived : public Base
{
public:
	using Base::mf1;
	using Base::mf2;
	using Base::mf3;
	virtual void mf1() { cout << "Dervied::mf1()" << endl; }
	void mf3() { cout << "Dervied::mf3()" << endl; }
};

class PrivDerived: private Base
{
public:
	void mf1() override {}
	void mf1(double x)
	{
		cout << "PrivDerived::mf1(): calling Base::mf1(double)" << endl;
		Base::mf1(x);
	}
	void mf2(double x) override { cout << "PrivDerived::mf2(double)" << endl; }
};

int main()
{
	Derived d;
	d.mf1();	// "Dervied::mf1()"
	// d.mf1(2.33);		// error: the Derived::mf1() hides the Base::mf1(double) so compiler search by name, not signature
	d.mf2(1.9);	// derived don't have function named mf2, so it inherited from base
	d.mf2();		// derived don't have function named mf2, so it inherited from base
	d.mf3();
	// d.mf3(2.0);		// Base::mf3(double) is not a virtual function

	// but if we want to use the base function, we can just add using:, so all the function with the same name will be accessible in derived function
	NewDerived nd;
	cout << "NewDerived start" << endl;
	nd.mf1();		// although Base::mf1() is accessible, but the Dervied::mf1() if first be found: "Dervied::mf1()"
	nd.mf1(2.23);	// mf1 found in Base: "Base::mf1(double x)"
	nd.mf2();		// mf2 found in Base, and based on parameter: "Base::mf2()"
	nd.mf2(2.23); // mf2 found in Base, and based on parameter: "Base::mf2(double)"
	nd.mf3();       // mf3 found in Derived and Base, but based on parameter: "Base::mf3()"
	nd.mf3(2.23);   // mf3 found in Derived and Base, but based on parameter: "Base::mf3(double)"

	// if you don't want all the function, first it's impossible in public inherited(think why)
	// a approach is using forwarding function
	PrivDerived pd;
	pd.mf1(2.9);
	pd.mf1();
	// pd.mf2(); can't directly call the inherited function
	pd.mf2(1.1);	// but a override public on can
}