#include <iostream>
#include <string>

using namespace std;

// assuming it's the raw resource type
class FontHandle
{
	
};

class Font
{
public:
	explicit Font(FontHandle fh): f(fh) {}
	// a explicit way to get the raw resource
	FontHandle get() const { return f; }
	// class-type conversation
	operator FontHandle() const { return f; }
private:
	FontHandle f;
};

void NeedRawFontHandle(FontHandle)
{
	
}

int main()
{
	Font f = Font(FontHandle());
	// some times, like C-API, they need access of raw resources
	// smart pointers have a .get() function to return the origin pointer(of cause it's a copied one)
	// use of .get(), it's explicit function, may cause users not willing to use
	NeedRawFontHandle(f.get());
	// and the implicit way:
	// add a class-type conversation
	NeedRawFontHandle(f);

	// but the implicit way may cause error, like:
	FontHandle f2(f);
	// so now we have a copy of raw resource, and if the origin one is freed, the f2 may be dangling

	// to use implicit or explicit, depends on your RAII class usage. there is no better one

	// and remember, get raw resource, don't break encapsulation.
	// In fact, RAII, using a object to manage resource is more focused on free resource than encapsulation
	return 0;
}