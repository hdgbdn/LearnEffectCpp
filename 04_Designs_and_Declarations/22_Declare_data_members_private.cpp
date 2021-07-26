#include <iostream>
#include <string>

using namespace std;

class AccessLevels
{
public:
	int getReadOnly() const { return readOnly; }
	int setReadWrite(int value) { readWrite = value; }
	int getReadWrite() const { return readWrite; }
	int setWriteOnly(int value) { writeOnly = value; }
private:
	int noAccess;
	int readOnly;
	int readWrite;
	int writeOnly;
};

class SpeedDataCollection
{
public:
	void addValue(int speed);
	double averageSoFar() const;
};

int main()
{
	// use function can prevent users confusion using class.member or class.member(), just use function version: class.member()
	// and provide different access level, because function contains logic, data member is just a object
	// see class AccessLevels above

	// encapsulation
	// like class SpeedDataCollection above, we can achieve different calculation method of average speed, like update a data member
	// which store the average speed every time a new record is in, it is fast but cost more space. Or only calculate when called,
	// it is slow, but cost less.
	// so for users, they just need to call the averageSoFar() function, we can easily change the implement without change users' code

	// for protected keyword, it has no more encapsulation than public, why?
	// if we cancel a public member, it affects unknown but a large amount of code, so does the protected one
	// so does the protected one, it affects unknown but a large amount of derived classes.

	// summary:
	// only private(encapsulation) or others(no encapsulation)
}