#include <iostream>
#include <string>

class Shape
{
public:
	virtual void draw() const = 0 { std::cout << "Base class's pure virtual function still can have definition" << std::endl; }
	virtual void error(const std::string& msg) {};
	int objectID() const  {};
};

class Rectangle : public Shape
{
	virtual void draw() const override { std::cout << "Rectangle::draw()" << std::endl; }
};

class Ellipse : public Shape
{

};

class AirPort{};
class AirPlane
{
public:
	virtual void fly(const AirPort& des){ std::cout << "AirPlane::fly()" << std::endl; }
	virtual void defaultFly(const AirPort& des) const = 0 { std::cout << "AirPlane::defaultFly()" << std::endl; }
};

class ModelA : public AirPlane
{
	// the definition of pure virtual function is used here
	void defaultFly(const AirPort& des) const override { AirPlane::defaultFly(des); }
};
class ModelB : public AirPlane
{
	void defaultFly(const AirPort& des) const override{ std::cout << "ModelB::defaultFly()" << std::endl; };
};

int main()
{
	// inherit only interfaces(declaration); inherit interface and implementation, but override some of the implementation

	// the Shape class, has three functions: pure virtual draw, impure virtual error and non-virtual objectID
	// pure virtual function: this is interface, means all the derived classes must give a definition,
	// and surprisingly, we can give base class's pure virtual function a definition, talk later
	Shape* p = new Rectangle();
	p->draw();
	p->Shape::draw();

	// impure virtual function error, it provides a interface and a implementation, if derived class don't override it, it may use a default version
	// the dangerous is that you may forget to override it, and the default behavior may not be the one you expected in the new derived class
	// like the airplane class
	AirPort airPort;
	AirPlane* pa = new ModelA();
	pa->fly(airPort);
	// but if we add a new model, and have a different fly method, and engineers forgot to override it, it will use the default version
	// and compiler won't give and error warning, causing a big mistake
	AirPlane* pb = new ModelB();
	pb->fly(airPort);
	// how to solve it?

	// first method, move base's default fly code into a protected function called defaultFly, then make the origin fly method pure virtual,
	// so derived class have to define their own, avoid directly inherit from base, and also provide a inline function defaultFly for convince

	// and some people may think their are two similar functions may confusion, here, defining a pure virtual function talked before
	// see defaultFly, so we makes derived class have to define their own version, and don't need to provide anther function to do the default

	// last, the Shape::objectID(), means that it is a interface, and don't want derived class to override it, but be careful derived class may hiding it, see rule 33,
	
	// so pure virtual means only interface, no implementation, impure virtual mean interface with overrideable implementation, and non virtual means interface and force implementation
}