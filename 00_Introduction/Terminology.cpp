#include <iostream>
#include <functional>

using namespace std;

//--- declaration
// complier only know the name

extern int x;

// size_t: just a unsigned typedef
// function signature: args and return type
std::size_t numDigits(int number);
class Wiget;

template <typename T>
class GraphNode;
//--- declaration

//--- definition
// now compiler gives them memory
// but the vlaue is not initialized
int x;
std::size_t numDigits(int number)
{
    std::size_t digitsSoFar = 1;

    while((number /= 10) != 0) ++digitsSoFar;
    return digitsSoFar;
}
class Widget{
public:
    Widget();
    ~Widget();
};
template <typename T>
class GraphNode{
public:
    GraphNode();
    ~GraphNode();
};
//--- definition

//--- Initialization
// give the initial value to objects
// for user class, it's construction
class A{
public:
    A();
};

class B{
public:
    explicit B(int x = 0, bool b = true) { cout << "B default constructor" << endl; };
};

class C{
public:
    explicit C(int x);
};
//--- Initialization


int main()
{
    // implicit type conversions and explicit type conversions
    {
        auto doSomething = [](B bObject)
        {
            return;
        };

        B bObj1;
        doSomething(bObj1); // correct, pass a B type object to function
        B bObj2(28);        // correct, int x = `28`, bool b = true
        // doSomething(28);        // error, implicit type conversions and explicit type conversions
        doSomething(B(28)); // correct, actualy it's a cast, from int to B;
    }

    // copy constructor & copy assignment
    {
        class Widget{
        public:
            Widget() { cout << "using default constructor" << endl; }                           // default
            Widget(const Widget& rhs) { cout << "using copy constructor" << endl; }             // copy
            Widget& operator=(const Widget& rhs) { cout << "using copy assignment" << endl; return *this; }   // copy assignment
        };

        Widget w1;          // using default constructor
        Widget w2(w1);      // using copy constructor
        w1 = w2;            // using copy assignment

        // becareful, operator '=' also can call copy constructor!
        Widget w3 = w1;     // using copy constructor

        // copy constructor defines "passed by value"
        auto Foo = [](Widget w){
            return;
        };

        cout << "pass value to function Foo" << endl;
        Foo(w3);        // using copy constructor
    }

    // undeined behavior
    {
        int* p = 0;
        cout << *p << endl;     // undefined behavior, because point to null
        char name[] = "Darla";
        char c = name[10];      // out range char index, causing undefined behavior
    }
}