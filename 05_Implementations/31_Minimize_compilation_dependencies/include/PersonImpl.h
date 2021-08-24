#ifndef PERSON_IMPL_H_
#define PERSON_IMPL_H_

#include <string>
#include "Address.h"
#include "Date.h"

class PersonImpl
{
public:
	PersonImpl(const std::string& name, const Date& birthday, const Address& addr): theName(name), theDate(birthday), theAddress(addr){}
	std::string name() const { return theName; }
	Date date() const { return theDate; }
	Address address() const { return theAddress; }
private:
	std::string theName;
	Date theDate;
	Address theAddress;
};

#endif