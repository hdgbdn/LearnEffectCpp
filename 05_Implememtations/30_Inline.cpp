#include <iostream>
#include <string>

class Person
{
public:
	int age() const { return theAge; }		// it's inline
private:
	int theAge;
};

inline void f() {}
void (*pf) () = f;

int main()
{
	// for some short function, the cost of inline maybe less than a function call! so the pros are less object code and more cache friendly
	// inline is just a suggestion to compiler, so compiler may reject it.
	//
	// for template functions, inline may cause more code, so be careful
	// 
	// why inline must defined in header file
	// because compiler should know the exact function when try to replace function call with function code
	// 
	// c++'s inline occurs during compiling, it means the runtime inline is impossible
	// virtual function ignore inline, because it happens in runtime

	// pointer and inline
	// see f() and pf()
	// f can be inline, but pf may outline, means compiler will generate a outline function, because pf needs the pointer of a function, which an inlined function don't have
	f();
	pf();

	// constructor and destructor are not suitable candidates for inline
	// even your defined an empty constructor or destructor, there will still be codes inside
	// because compiler will add code inside to make sure like call base constructor in construction, deconstruct base part when exception occurs during base construction
	// and so on. so if your want to inline a constructor or destructor, you should consider you are inlining more than you see
	// and even you try to inline the base's constructor or destructor, you should remember that all the derived object will get a copy of that code

	// and if a inline function is changed, all the reference of this function will need to be recompiled, because they need re-inline all the function
	// and non-inline function just need re-link

	// and also inline is hard for debugging because the function is not exited during runtime
	
	return 0;
}