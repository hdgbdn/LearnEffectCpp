#include <iostream>
#include <string>

using namespace std;

class Investment
{
	
};

Investment* createInvestment()
{
	return new Investment();
}

int main()
{
	{
		Investment* pInv = createInvestment();
		// if something happens here, can be exception, return or anything that causes the function abort before the delete
		// the memory is leaked
		delete pInv;
	}
	// RAII, Resource Acquisition Is Initialization, acquiring resource and put in under some managing object at the same time.
	// and we can rely on c++'s automatic destruction to release the resource with objection destruction.
	{
		shared_ptr<Investment> pInv1(createInvestment());
	}

	// shared_ptr use delete not delete[], because std thinks vector and string it a better choice when managing dynamic arrays.

	// Summary:
	// RAII, use object to manage raw resource, because we can benefit from managing object, that's after leaving scope or exception
	// compiler will automatic call destructor, and free the memory

	// shared_ptr has a con: two shared_ptr pointed to each other, and be careful, shared_ptr use delete, not delete[], so don't store array
}