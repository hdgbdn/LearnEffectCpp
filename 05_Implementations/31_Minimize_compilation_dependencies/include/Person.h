#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <memory>
#include "Datefwd.h"

class PersonImpl;
class Address;

// Person.h is just a interface class, the implement is in PersonImpl.h
// PersonImpl, Date, don't need know their definition because we just use them as reference and pointer
// and event Address is passed by value, still don't need definition

// the Datefwd only provide declaration, but function Date birthDate() and Person(const std::string& name, const Date& birthday, const Address& addr)
// throw no error, because they have the name and don't need the detail, but why use fwd file instead of just declare in head?
// because it's better to use a file to manage the declaration than manually declare in every file which use the name.
class Person
{
public:
	Person(const std::string& name, const Date& birthday, const Address& addr);
	std::string name() const;
	Date birthDate() const;
	Address address() const;
	void test() {};
private:
	std::shared_ptr<PersonImpl> pImpl;
};


#endif