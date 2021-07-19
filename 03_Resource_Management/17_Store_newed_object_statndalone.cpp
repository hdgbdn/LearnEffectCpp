#include <iostream>
#include <string>
#include <memory>

int SomeOperation();

class Widget{};

void processWiget(std::shared_ptr<Widget>, int) {}

int main()
{
	processWiget(std::shared_ptr<Widget>(new Widget), SomeOperation());
	// seems ok, but there are three operations: new Widget, shared_ptr<Widget> constructor, and SomeOperation()
	// compiler can arrange the order, so, it's possible that new Widget, then SomeOperation(), then shared_ptr<Widget> constructor
	// if SomeOperation() cause exception, then the newed Widget may lost, because the shared_ptr<Widget> constructor may not be called
	// so it's necessary to split the new and shared_ptr<Widget> constructor, like
	std::shared_ptr<Widget> pw(new Widget);
	processWiget(pw, SomeOperation());
	// compiler can't arrange order by different statements
	return 0;
}