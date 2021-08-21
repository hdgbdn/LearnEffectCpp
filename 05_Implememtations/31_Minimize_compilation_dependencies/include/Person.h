#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <memory>

class PersonImpl;
class Date;
class Address;

// Person.h is just a interface class, the implement is in PersonImpl.h
class Person
{
public:
	Person();
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
private:
	std::shared_ptr<PersonImpl> pImpl;
};


#endif