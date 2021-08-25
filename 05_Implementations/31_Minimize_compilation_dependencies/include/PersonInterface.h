#ifndef PERSONINTERFACE_H_
#define PERSONINTERFACE_H_

#include <memory>
#include <string>

class Date;
class Address;
class RealPerson;

class PersonInterface
{
public:
	virtual ~PersonInterface() {};
	virtual std::string name() const = 0;
	virtual Date birthDate() const = 0;
	virtual Address address() const = 0;
	static std::shared_ptr<PersonInterface> create(const std::string& name, const Date& data, const Address& addr);
};

#endif // !PERSONINTERFACE_H_
