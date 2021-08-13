#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Window
{
public:
	virtual void SomeVirtualFunc() { cout << s << endl; };
	virtual void onResize() {};
private:
	string s;
};

class WindowWithScrollBar: public Window
{
public:
	void windowWithScrollBarFunc() { cout << "windowWithScrollBarFunc" << endl; }
	virtual void SomeVirtualFunc() override { cout << s << endl; };
	virtual void onResize() override { static_cast<Window>(*this).onResize(); };		// genius,
private:
	string s;
};

void ConstCast(const string& str)
{
	const_cast<string&>(str) = "const cast";
}

int main()
{
	int i = 3;
	// c style casting
	cout << (double)i << endl;
	// function style casting
	cout << double(i) << endl;
	// both call the constructor

	// C++-style casts
	const string cs = "abc";
	string s = "abc";
	const string& rs = s;
	const string* ps = &s;
	// only can remove constness from const pointer or reference to a non const variable
	// const_cast<string>(s); // error, can't remove constness
	const_cast<string&>(rs) = "def";
	cout << "changed const reference is " << rs << endl;
	*const_cast<string*>(ps) = "ghi";
	cout << "changed const pointer is " << *ps << endl;
	string s2("test");
	cout << "before const cast: " << s2 << endl;
	ConstCast(s2);
	cout << "after const cast: " << s2 << endl;

	// cast between base pointer and derived pointer
	// book says a base pointer point to a derived object may not have same address as the derived pointer point to the same derived object
	// but I don't know how to show it, the example below print the same address
	WindowWithScrollBar wsb;
	WindowWithScrollBar* pwsb1 = &wsb;
	WindowWithScrollBar* pwsb2 = &wsb;
	Window* pw = &wsb;
	cout << "Derived pointer address1 is " << pwsb1 << endl;
	cout << "Derived pointer address2 is " << pwsb2 << endl;
	cout << "Base pointer address is " << pw << endl;

	// try to use static_cast to call the base function, see WindowWithScrollBar::onResize
	// the static_cast<Window>(*this) returns a copy of current WindowWithScrollBar object, so the static_cast<Window>(*this).onResize() just called
	// the onResize() function on a temp Window object, the real base part will not be changed!
	// just use Window::onResize()

	// dynamic_cast: safe downcasting, object is belong to a inherent system
	// first, dynamic cast is very slow
	// sometimes you need dynamic_cast because you only have a base pointer but you want to call the derived function
	{
		WindowWithScrollBar wsb;
		Window* pw = &wsb;
		Window* pw2 = new Window();
		// pw2->windowWithScrollBarFunc();		// error: no member "windowWithScrollBarFunc"
		dynamic_cast<WindowWithScrollBar*>(pw)->windowWithScrollBarFunc();
		dynamic_cast<WindowWithScrollBar*>(pw2)->windowWithScrollBarFunc();
	}

	// two ways to avoid it
	// first, container stores the derived pointer other than stores the base pointer
	vector<shared_ptr<WindowWithScrollBar>> VPWSB;
	vector<shared_ptr<Window>> VPW;
	// second, use empty virtual function
	// class Window{ ... virtual void windowWithScrollBarFunc(); }
	return 0;
}