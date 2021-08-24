#ifndef ADDRESS_H_
#define ADDRESS_H_
#include <string>
class Address
{
public:
	Address(const std::string& a): addr(a) {}
private:
	std::string addr;
};

#endif // !ADDRESS_H_
