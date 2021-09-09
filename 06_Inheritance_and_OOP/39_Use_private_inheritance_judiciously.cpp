#include <iostream>
#include <string>
#include "39_Widget.h"

class Person{};

class Student : private Person{};

void eat(const Person&) {}

class Timer
{
public:
	virtual void onTick() const { std::cout << "Timer::onTick()" << std::endl; }
};

class PrivateWidget : private Timer
{
private:
	virtual void onTick() const override { std::cout << "PrivateWidget::onTick()" << std::endl; }	// although it's private inheritance, still can override virtual function
};

class CompoWidget
{
private:
	class WidgetTimer:public Timer
	{
	public:
		virtual void onTick() const override { std::cout << "CompoWidget::WidgetTimer:onTick()" << std::endl; }
	};
};

int main()
{
	// private inheritance is not "is-a"
	Person p;
	Student s;
	eat(p);
	//eat(s);		// conversation to inaccessible base: Person is not allowed
	// so, what does a private inheritance mean?
	// it means implemented-in-terms-of, like composition, means a part of derived class's implementation is based on base class
	// don't mean that B and D has some concept relation

	// example: we want a widget to have timer's function
	// why public inheritance is not appropriate here? because public inheritance means "is-a"
	// but widget is not a timer. so use private here make widget is implemented-in-terms-of timer
	// and we can override the onTick function
	PrivateWidget pw;
	// pw.onTick();		// the onTick function is just for Private widget itself
	// but private inheritance is not a great idea, see CompoWidget
	// we public inherit the timer as a private class member WidgetTimer declared in the private scope of CompoWidget
	// so the this widget can only be used by CompoWidget, and can also is-a Timer;

	// two benefits:
	// 1: derived classes of CompoWidget can not redefine the widget time, so it's kind like "final"
	// 2: use WidgetTimer as a member means we can split definition and declaration.
	// if we use private inherit, then we have to include the "Timer.h", but if we use pimpl,
	// the class WidgetTimer is a pointer member of CompoWidget, then the CompoWidget file don't need to include "Timer.h"
	// just need "class WidgetTimer", even don't need "class WidgetTimer: public Timer"
	TestWidget tw;

	// so when to use private inherit? when you face two classes, they are not "is-a" but one need to access the others protected member
	// or override some virtual functions.
	// but both can be achieved by using public inherit and composition(like CompoWidget)

	return 0;
}