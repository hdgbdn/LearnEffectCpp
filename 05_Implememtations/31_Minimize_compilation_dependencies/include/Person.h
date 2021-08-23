#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <memory>

class PersonImpl;
class Date;
class Address;

// Person.h is just a interface class, the implement is in PersonImpl.h
// PersonImpl, Date, don't need know their definition because we just use them as reference and pointer
// and event Address is passed by value, still don't need definition
class Person
{
public:
	Person(const std::string& name, const Date& birthday, const Address& addr);
	std::string name() const;
	Date birthDate() const;
	Address address() const;
private:
	std::shared_ptr<PersonImpl> pImpl;
};


#endif