#include "Person.h"
#include <string>
#include "Address.h"
#include "Date.h"

class PersonImpl
{
public:
	PersonImpl(const std::string& name, const Date& birthday, const Address& addr) : theName(name), theDate(birthday), theAddress(addr) {}
	std::string name() const { return theName; }
	Date date() const { return theDate; }
	Address address() const { return theAddress; }
private:
	std::string theName;
	Date theDate;
	Address theAddress;
};

Person::Person(const std::string& name, const Date& birthday, const Address& addr): pImpl(new PersonImpl(name, birthday, addr)) {}

std::string Person::name() const
{
	return pImpl->name();
}

Address Person::address() const
{
	return pImpl->address();
}

Date Person::birthDate() const
{
	return pImpl->date();
}



