#include <iostream>
#include <string>
#include <memory>

using namespace std;

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

TimeKeeper* getTimeKeeper(int i)
{
	if (i == 0) return new AtomicClock();
	if (i == 1) return new WaterClock();
	return new WristWatch();
}

int main()
{
	// getTimeKeeper is a factory function, return a base class pointer, point to the new derived object
	// so user just have to know the base class, don't need to know the detail classes
	TimeKeeper* ptk = getTimeKeeper(1);
	delete ptk;
	// the result is that only the base class's destructor is been called

	// be careful with the delete, we delete a base pointer which is pointed to a derived object,
	// so if the base class has an non-virtual destructor, then the derived part will possibly not be destroyed
	return 0;
}