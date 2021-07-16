#include <iostream>
#include <string>

using namespace std;

class Transaction
{
public:
	Transaction();
	virtual void logTransaction() const { cout << "log Transaction" << endl; };
	void init() { logTransaction(); }
};

Transaction::Transaction()
{
	// directly use pure virtual function, compiler will find error:
	// result a pure virtual function call
	// logTransaction();

	// but wrap with member function
	init();
}


class BuyTransaction: public Transaction
{
public:
	BuyTransaction();
	void logTransaction() const override;
};

BuyTransaction::BuyTransaction(): Transaction(){}

void BuyTransaction::logTransaction() const
{
	cout << "log BuyTransaction" << endl;
}


class SellTransaction: public Transaction
{
public:
	SellTransaction();
	void logTransaction() const override;
};

SellTransaction::SellTransaction(): Transaction(){}

void SellTransaction::logTransaction() const
{
	cout << "log SellTransaction" << endl;
}

class NewTransaction
{
public:
	explicit NewTransaction(const string& logInfo);
	void logTransaction(const string& logInfo);
};

NewTransaction::NewTransaction(const string& logInfo)
{
	logTransaction(logInfo);
}

void NewTransaction::logTransaction(const string& logInfo)
{
	cout << logInfo << endl;
}



class NewBuyTransaction: public NewTransaction
{
public:
	static string createLogString() { return "NewBuy"; }
	NewBuyTransaction(): NewTransaction(createLogString()) {}
};

int main()
{
	// the design is good: when we constructing a derived object, call the virtual function so different type will log differently
	// and we call the virtual function in base type constructor, so that every derived class will call their version's function when calling the base constructor
	// but during constructing the base part of a derived class, the virtual function is not virtual function, it belongs the type which is constructing
	
	BuyTransaction bt;
	SellTransaction st;

	// so remember, in constructor, don't use virtual function, and also don't use function that calls virtual function

	// a better solution is to pass the information from derived to base
	NewBuyTransaction nbt;
}