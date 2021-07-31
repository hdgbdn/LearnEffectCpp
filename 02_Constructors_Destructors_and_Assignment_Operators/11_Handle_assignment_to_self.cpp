#include <iostream>
#include <string>

#define IDENTITY_TEST
using namespace std;

class BitMap
{
public:
	BitMap(const string& s): name(s){};
	BitMap(const BitMap& bm)
	{
		throw(out_of_range("Throw a exception when copy constructing"));
	}
	string name;
};

class Widget
{
public:
	Widget(const string& s): pb(new BitMap(s)){}
	Widget& operator=(const Widget&);
	BitMap* pb;
};

Widget& Widget::operator=(const Widget& rhs)
{
#ifdef NON_SAFE
	delete pb;
	pb = new BitMap(*rhs.pb);
#endif

#ifdef IDENTITY_TEST
	if (this == &rhs) return *this;
	delete pb;
	pb = new BitMap(*rhs.pb);
#endif

#ifdef EXCEPTION_SAFE
	BitMap* pOrig = pb;
	// if exception happens, then pb remain origin, because the delete will be executed
	pb = new BitMap(*rhs.pb);
	cout << "delete pb" << endl;
	delete pOrig;
#endif

#ifdef COPY_SWAP
	Widget temp(rhs);
	using std::swap;
	swap(temp, *this);
#endif
	
	return *this;
}

int main()
{
	// because of aliasing, some operation actually is self-assignment
	// like: a[i] = a[j], *px = *py or const Base& and const Derived*

	// self-assignment-safe
	// check if the operand is the same as *this, but it's not exception safe, because if 'new' cause exception, then pd will become a dangling pointer
	//
	// exception safe
	// we put delete operation after new, so even if 'new' cause exception, pd still holds the origin one
	// and it's also self-assignment-safe because it's copy construct a new BitMap

	// copy and swap
	// copy construct a new object using argument, then swap it with *this

	// and a even tricky method is to use pass-by-value, to move copy from function to the value passing
	/*
	Widget& Widget::operator=(Widget rhs){
		using std::swap;
		swap(temp, *this);
		return *this;
	}
	 */
	Widget w1("w1");
	Widget w2("w2");
	try
	{
		w1 = w2;
	}
	catch (const out_of_range& or)
	{
		// if don't use EXCEPTION_SAFE, then w1.pd will become a dangling pointer
		cout << or.what() << endl;
		cout << "w1's bitmap name is " << w1.pb->name << endl;
	}

	// Summary:
	// when self-assigning, you may change the data member of 'this', but the rhs is also 'this', so your permanently lost the data
	// one way is identity test: check if the rhs equals this, but it don't consider the exception safe.
	// in other words, exception safe can automatically brings self-assigning:
	// 1: make sure when exception happens, the data remain unchanged
	// or, use copy and swap(and a tricky version);
	
	return 0;
}