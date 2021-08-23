#include "Person.h"
#include "PersonImpl.h"

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



