#ifndef REALPERSON_H_
#define REALPERSON_H_

#include "PersonInterface.h"

class RealPerson :public PersonInterface
{
public:
	virtual ~RealPerson() override;
	virtual std::string name() const override;
	virtual Date birthDate() const override;
	virtual Address address() const override;
};

#endif