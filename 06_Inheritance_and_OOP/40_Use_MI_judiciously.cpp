#include <iostream>
#include <string>

#define USE_VIRTUAL_INHERITANCE

class Student
{
public:
	std::string getID() { return "Student's ID"; }
};

class Worker
{
private:
	std::string getID() { return "Worker's ID"; }
};

class Arubaito: public Student, public Worker{};

class Monitor
{
public:
	Monitor(): Model("Base Monitor") {}
	Monitor(const std::string &model): Model(model) {}
	std::string Model;
};

class Monitor4K:
#ifdef USE_VIRTUAL_INHERITANCE
	public virtual Monitor
#else
	public Monitor
#endif
{
public:
	Monitor4K() : Monitor("4K Monitor") {}
};
class MonitorPortable:
#ifdef USE_VIRTUAL_INHERITANCE
	public virtual Monitor
#else
	public Monitor
#endif
{
public:
	MonitorPortable() : Monitor("Portable Monitor") {}
};

class Monitor4KPortable: public Monitor4K, public MonitorPortable
{
public:
	Monitor4KPortable(): Monitor4K(), MonitorPortable() {}
};

class IPerson
{
public:
	virtual ~IPerson();
	virtual std::string name() const = 0;
	virtual std::string birthDay() const = 0;
};

class DatabaseID{};

class PersonInfo
{
public:
	explicit PersonInfo(DatabaseID pid){}
	virtual ~PersonInfo();
	virtual const char* theName() const;
private:
	virtual const char* valueDelimOpen() const
	{
		return "[";
	}
	virtual const char* valueDelimClose() const
	{
		return "]";
	}
};

const char* PersonInfo::theName() const
{
	static char value[256];
	std::strcpy(value, valueDelimOpen());
	std::strcpy(value, "myname");
	std::strcpy(value, valueDelimOpen());
	return value;
}

class CPerson : public IPerson, private PersonInfo
{
public:
	explicit CPerson(DatabaseID pid) : PersonInfo(pid) {}
	virtual std::string name() const override { return PersonInfo::theName(); }
private:
	const char* valueDelimOpen() const override { return ""; }
	const char* valueDelimClose() const override { return ""; }
};

int main()
{
	// if a student in summer vacation want to アルバイト, then he is both a student and worker
	// but the two classes share the same getID function, and have different access level, how to deal with it?
	// it is so-called multiple inheritance, we could specify which function to call
	Arubaito taro;
	std::cout << "Taro kun no student ID is " << taro.Student::getID() << std::endl;

	// but how about the inheritance system Monitor4KPortable? a class derived from multiple classes which share the same base
	// what is the member ID?
	Monitor4KPortable myNewMonitor;
	std::cout << "My new monitor's model is " << myNewMonitor.Monitor4K::Model << std::endl;
	std::cout << "But also can be " << myNewMonitor.MonitorPortable::Model << std::endl;
	// if don't use virtual inheritance, then the output are "4K Monitor" and "Portable Monitor"
	// if use virtual inheritance, then the output are "Base Monitor" and "Base Monitor"
	// when using virtual inheritance, the synthesized constructor will be deleted.

	// last example shows how to correctly use MI: we need the interface of IPerson,
	// and we need implementation and a little override of PersonInfo,
	// so public inherit IPerson to inherit interface,
	// and private inherit PersonInfo to use implementation
}