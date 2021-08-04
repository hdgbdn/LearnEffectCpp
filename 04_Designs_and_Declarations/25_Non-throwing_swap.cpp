#include <iostream>
#include <string>
#include <vector>

class WidgetImpl
{
private:
	int a, b, c;
	std::vector<double> v;
};

class Widget
{
public:
	Widget() :pImpl(new WidgetImpl()) {}
	Widget(const Widget& rhs): pImpl(nullptr)
	{
		pImpl = new WidgetImpl(*rhs.pImpl);
	}
	Widget& operator=(const Widget& rhs)
	{
		delete pImpl;
		*pImpl = *rhs.pImpl;
	}
	void swap(Widget& other)
	{
		using std::swap;			// important!!!!!!
		swap(pImpl, other.pImpl);
	}
private:
	WidgetImpl* pImpl;
};

/*
namespace std
{
	template<>
	void swap<Widget>(Widget& a, Widget& b)
	{
		swap(a.pImpl, b.pImpl);
	}
}
 */

// why specialized template not found?
/*
 namespace std {
	template<>
	void swap<Widget>(Widget& a, Widget& b) {
		a.swap(b);
	}
}
 */

namespace TemplateWidgetStuff
{
	template<typename T>
	class TemplateWidget
	{
	public:
		TemplateWidget() :pImpl(new WidgetImpl()) {}
		TemplateWidget(const TemplateWidget& rhs) : pImpl(nullptr)
		{
			pImpl = new WidgetImpl(*rhs.pImpl);
		}
		TemplateWidget& operator=(const TemplateWidget& rhs)
		{
			delete pImpl;
			*pImpl = *rhs.pImpl;
		}
		void swap(TemplateWidget& other)
		{
			using std::swap;			// important!!!!!!
			swap(pImpl, other.pImpl);
		}
	private:
		WidgetImpl* pImpl;
	};
	// final try: declare in the class's namespace
	template<typename T>
	void swap(TemplateWidget<T>& a, TemplateWidget<T>& b) {
		a.swap(b);
	}
}


// first try: partially specialize a function template
// illegal! partially specialize a function template is not allowed
/*
namespace std
{
	template<typename T>
	void swap<TemplateWidget<T>>(TemplateWidget<T>& a, TemplateWidget<T>& b) {
		a.swap(b);
	}
}
 */

// second try, override a function template in std
// but c++ not recommend to add new templates into std
/*
namespace std
{
	template<typename T>
	void swap(TemplateWidget<T>& a, TemplateWidget<T>& b) {
		a.swap(b);
	}
}
 */

int main()
{
	// main topic: you can declare your own swap function, but it involved in some function namespace trouble

	// class Widget has a pImpl pointer, for swap operation, we just need to swap their pIml, don't need to create a temp object;
	// but how to declare our own swap function?

	// first, declare in what namespace? std?
	// it will become a total template specialization
	// but usually std don't suggest us to change, and the non member non friend function can't access the private member
	// mark it as friend? no, we said before prefer use non friend function to keep encapsulation.
	// so another choice is to make a member class, see above

	// but what if widget is a template? see the three attempts above

	// why use using std::swap? because of name lookup rules: if the T version swap exits, then ADL will find, if not, then use the std one

	// add: the c++ 11 uses std::move, so, the std version swap may works as good as your own( if have a proper move constructor)
	return 0;
}