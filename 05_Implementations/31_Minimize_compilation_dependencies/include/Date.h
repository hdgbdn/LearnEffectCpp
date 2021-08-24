#ifndef DATE_H_
#define DATE_H_

#include <string>

class Date
{
public:
	Date(const std::string d): date(d){}
private:
	std::string date;
};

#endif
