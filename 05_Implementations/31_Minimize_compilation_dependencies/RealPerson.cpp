#include "RealPerson.h"
#include "Date.h"
#include "Address.h"

RealPerson::~RealPerson()
{
	
}


Address RealPerson::address() const
{
	int i = 1;
	return Address("test");
}

Date RealPerson::birthDate() const
{
	return Date("test");
}

std::string RealPerson::name() const
{
	return "test";
}

std::shared_ptr<PersonInterface> PersonInterface::create(const std::string& name, const Date& data, const Address& addr)
{
	return std::make_shared<RealPerson>();
}

