#include <iostream>
#include <string>
#include <memory>

using namespace std;

//-------------Without virtual destructor
class TimeKeeper
{
public:
	TimeKeeper() = default;
	~TimeKeeper() { cout << "TimeKeeper destructor" << endl; }
};

class AtomicClock : public TimeKeeper
{
	~AtomicClock(){ cout << "AtomicClock destructor" << endl; }
};
class WaterClock  : public TimeKeeper
{
	~WaterClock() { cout << "WaterClock destructor" << endl; }
};
class WristWatch  : public TimeKeeper
{
	~WristWatch() { cout << "WristWatch destructor" << endl; }
};
//-------------Without virtual destructor

//-------------With virtual destructor
class VTimeKeeper
{
public:
	VTimeKeeper() = default;
	virtual ~VTimeKeeper() { cout << "VTimeKeeper destructor" << endl; }
};

class VAtomicClock : public VTimeKeeper
{
	~VAtomicClock() { cout << "VAtomicClock destructor" << endl; }
};
class VWaterClock : public VTimeKeeper
{
	~VWaterClock() { cout << "VWaterClock destructor" << endl; }
};
class VWristWatch : public VTimeKeeper
{
	~VWristWatch() { cout << "VWristWatch destructor" << endl; }
};
//-------------With virtual destructor

TimeKeeper* getTimeKeeper(int i)
{
	if (i == 0) return new AtomicClock();
	if (i == 1) return new WaterClock();
	return new WristWatch();
}

VTimeKeeper* getVTimeKeeper(int i)
{
	if (i == 0) return new VAtomicClock();
	if (i == 1) return new VWaterClock();
	return new VWristWatch();
}

//------------inherit a class without virtual destructor
class MyString: public string
{
public:
	~MyString() { cout << "my string destructor" << endl; }
};

class AWOV
{
public:
	virtual ~AWOV() = 0;
};

AWOV::~AWOV(){	}


int main()
{
	// getTimeKeeper is a factory function, return a base class pointer, point to the new derived object
	// so user just have to know the base class, don't need to know the detail classes
	TimeKeeper* ptk = getTimeKeeper(1);
	delete ptk;
	// the result is that only the base class's destructor is been called

	// be careful with the delete, we delete a base pointer which is pointed to a derived object,
	// so if the base class has an non-virtual destructor, then the derived part will possibly not be destroyed

	// with virtual destructor
	VTimeKeeper* vptk = getVTimeKeeper(1);
	// out put:
	// VWaterClock destructor
	// VTimeKeeper destructor
	// both base and derived object's destructor are called
	delete vptk;

	// note: a class with a virtual function must have a virtual destructor
	// a class without virtual function means it won't be a base class
	// because define a virtual function will cost more than normal function, if don't use polymorphic
	// then don't use virtual function

	// and don't try to inherit a class without virtual destructor
	// obviously, you derived class will not be successfully destructed
	MyString* p = new MyString();
	delete p;	// my string destructor
	// but it don't work, maybe now string has a virtual destructor?
	// in new standard, we can use final to forbid inheritance.

	// what if we don't want to define any pure virtual function, but still want the class to be a abstract class?
	// declare a pure virtual destructor
	// but you have to define it, since as the base class, when destroying the derived class, compiler will call it's destructor
	// why normal pure function don't need definition? because they are not called by the compiler automatically.

	// summary:
	// if a class is a base class, it should have a virtual destructor, or base pointer will just call the base's destructor
	// a class with virtual function, must need a virtual destructor
	// don't declare virtual functions if a class isn't a base class, virtual function costs more than a normal function
	// don't derived a class without a virtual destructor
	// if we want a pure class and don't have any virtual function, we set the destructor as pure virtual function, but must provide definition.

	return 0;
}