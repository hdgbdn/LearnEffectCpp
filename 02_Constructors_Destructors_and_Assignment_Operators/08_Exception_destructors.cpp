#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ThrowE
{
public:
	ThrowE(): str(new string()){}
	~ThrowE()
	{
		try
		{
			throw(runtime_error("test"));
		}
		catch (const runtime_error& e)
		{
			cout << "catches runtime error" << endl;
			throw;
			// if throw the exception, it will cause a undefined behaviour, because destructor is part of exceptional handling
			// C++ can't handle a exception inside a exception
		}
		cout << "free string" << endl;
		delete str;
	}
private:
	string* str;
};

class ThrowE2
{
public:
	ThrowE2() : str(new string()) {}
	~ThrowE2()
	{
		try
		{
			throw(runtime_error("test"));
		}
		catch (const runtime_error& e)
		{
			cout << "catches runtime error" << endl;
			// don't throw exception, it's even better to stop the programe
			cout << "free string" << endl;
			delete str;
			std::abort();
		}
		cout << "free string" << endl;
		delete str;
	}
private:
	string* str;
};

class ThrowE3
{
public:
	ThrowE3() : str(new string()), closed(false) {}
	void close() { throw(runtime_error("test")); closed = true; }
	~ThrowE3()
	{
		if (closed) delete str;
		else
		{
			try
			{
				close();
			}
			catch (const runtime_error& e)
			{
				delete str;
			}
		}
	}
private:
	string* str;
	bool closed;
};

int main()
{
	// after throwing a exception, if exception are not successfully been caught, compiler will call terminate to stop current program
	// so is program is terminated during destruction, then some memory may not be freed.
	// So we should use try to handle where may cause a exception, and handle it in the destructor, not throw it out.
	{
		//ThrowE e;
		ThrowE2 e1;
	}
	// destructor is part of exceptional handling, when exception happens, c++ call destructor to clean the error object
	// but if destructor is throwing error again, then no one will handle this exception, so destructor should not throw exception
	// must handle it.

	// ThrowE's destructor throw the exception, so the string memory will not be free
	// ThrowE2 handles it, and free the memory

	// but not throw the exception means that user can't handle the exception
	// so a good solution is let user to call the function which may cause exception
	{
		ThrowE3 e;
		try
		{
			e.close();
		}
		catch (const runtime_error& e)
		{
			cout << "now user can handle exception" << endl;
		}
	}

	// Summary:
	// destructor is part of exceptional handling, when exception happens, c++ call destructor to clean the error object
	// but if destructor is throwing error again, then no one will handle this exception, so destructor should not throw exception

	// but user will not know the exception happens, so a better way is to let user to call the function which may throw a exception
	// and let user to handle it.
}