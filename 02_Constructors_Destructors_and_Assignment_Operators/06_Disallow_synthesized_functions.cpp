#include <iostream>
#include <string>

using namespace std;

// if you want house is uncopyable
// then what you should do?
// at the time the book wrote, we achieve this by declaring copy control functions private
// because if you don't declare one, compiler will declare their version

// but a little bit complex
// first declar a uncopyable class
class Uncopyable {
protected:
    Uncopyable() { cout << "Uncopyable constructor" << endl; }
    ~Uncopyable() { cout << "Uncopyable destructor" << endl; }
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

// private can't be accessed
class HomeForSale: private Uncopyable{

};

// in new standrad, use =delete
class NewUncopyable{
protected:
    NewUncopyable() {}
    ~NewUncopyable() {}
    NewUncopyable(const NewUncopyable&) = delete;
    NewUncopyable& operator=(const NewUncopyable&) = delete;
};

// remember if the base class prevents copy
// the derived class will not have a synthesized copy operation

class NewHomeForSale: private NewUncopyable{

};

int main()
{
    HomeForSale myHome;
    // HomeForSale hisHome(myHome);        // error: a deleted function
	// HomeForSale inherent from Uncopyable, the base class's constructor's constructor is private, so what will happen when we create a HomeForSale?
	// will the synthesized default constructor call the base's constructor?
	// the constructor will be called, because the constructor and destructor is protected, the derived class can access it.
    NewHomeForSale myNewHome;
    // NewHomeForSale hisHome(myNewHome);  // error: a deleted function
	// because the base class: NewUncopyable has deleted copy construction and assignment

	// Summary:
	// to prevent copy operations, we can set copy constructor and copy assignment as private, or in new standard, use '= delete'
	// and we can create a base class which copy operation is inaccessible(private or deleted), then derived class can't access it's base class's
	// copy operation, so it prevent compiler to synthesize copy operations. (but if you defined by yourself, then it is still copyable)
}