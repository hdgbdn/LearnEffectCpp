#include <iostream>
#include <string>
#include <memory>

class DateNum
{
public:
	DateNum(int month, int day, int year) {}
};

struct Day
{
	explicit Day(int d) : val(d) {}
	int val;
};

struct Month
{
	explicit Month(int m) : val(m) {}
	int val;
};

struct Year
{
	explicit Year(int y) : val(y) {}
	int val;
};

class DateStruct
{
public:
	DateStruct(const Month&, const Day&, const Year&) {};
};

//----------------------------
class ExplicitMonth
{
public:
	// why return in function?
	// because non-local static object's initialization may have order issues, user may get a uninited object;
	// like: static Jan(ExplicitMonth(1));
	static ExplicitMonth Jan() { return ExplicitMonth(1); }
	static ExplicitMonth Feb() { return ExplicitMonth(2); }
private:
	explicit ExplicitMonth(int m) {}
};

class NeedAMonth
{
public:
	NeedAMonth(const ExplicitMonth&) {}
};

class Investment
{

};

Investment* createInvestment()
{
	return new Investment;
}

std::shared_ptr<Investment> createInvestmentSmart()
{
	return std::shared_ptr<Investment>(new Investment);
}

void getRidOfInvestment(Investment* p)
{
	std::cout << "getRidOfInvestment" << std::endl;
	delete p;
}

std::shared_ptr<Investment> createinvestmentWithDeleter()
{
	// remember rule 17? store newed object in standalone statement, so don't new here
	std::shared_ptr<Investment>ret(static_cast<Investment*>(0), getRidOfInvestment);
	ret = std::shared_ptr<Investment>(new Investment);
	return ret;
}

int main()
{
	// 1: prevent incorrect use, use class to explicit parameters
	DateNum d1(99, 99, 99);	// so nothing to prevent this invalid input
	// DateStruct(3, 5, 6);									// error type
	// DateStruct(Day(30), Month(12), Year(1992));		// error type
	DateStruct(Month(12), Day(30), Year(1992));		// correct

	NeedAMonth m1(ExplicitMonth::Jan());

	// in consistence with build int types, such as illegal to a*b = c, your class better to behaviour like this
	// keep interface consistence, like vector, string, set, they have same size() to get size. java is a bad example, length, length(), Count.

	// minimize thing users need to do
	// bad example
	Investment* p = createInvestment();
	// user should remember delete it, it's unreliable
	delete p;

	// a better method is to return smart pointer
	std::shared_ptr<Investment> sp = createInvestmentSmart();	// RAII

	Investment* p2 = createInvestment();
	// if need user to handle raw resource because of having a unique operation when releasing the resource
	// it is also dangerous
	getRidOfInvestment(p2);
	// because user may direct use delete p2
	// so after leaving scope, the getRidOfInvestment is executed
	std::shared_ptr<Investment> sp2 = createinvestmentWithDeleter();

	// also wrap with shared_ptr can cross-DLL problem, like newed in one DLL, and deleted in other

	// but shared_ptr has other cost like twice the size of raw pointer, a dynamic memory to store it's data member
	// and call deleter using virtual function. it's heavy, but for decrease errors' purpose, it's good.

	// Summary
	// 1: specify type to avoid misleading multi parameters, like void(int, int, int) -> void(type1, type2, type3)
	// and remember how to deal with non-local static?

	// 2: make your class behaviour like build-in type, means consistence, also your class, same behaviour, same interface.

	// 3: make user remember as less as possible, like return smart pointer rather than raw pointer.
	// and use the deleter, if your have some additional operation when free the memory, rather than let user to call it.

	// 4: misc: create void smart pointer: shared_ptr<A>(static_cast<A*>(0), your_deleter), then a shared_ptr with no pointer, but
	// have a deleter, why don't new the object in this statement? rule 17: new object in a standalone statement;
	// and cross-DLL problem
	
	return 0;
}
