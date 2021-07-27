#include <iostream>
#include <string>

class Person
{
public:
	void pickPhone();
	void pickWallet();
	void pickKeys();
	void prepareToGoOut()
	{
		pickPhone();
		pickWallet();
		pickKeys();
	}
};

void prepareToGoOut(Person& person)
{
	person.pickPhone();
	person.pickWallet();
	person.pickKeys();
}

int main()
{
	// so which is better, the member one or the non-member non-friend one?
	// first, encapsulation
	// why? because a member version can access more data than a non-member non-friend version
	// since they can do the same job, the less their code can access, the more encapsulation they have
	// so for our class, the less we know from outside, then more flexibility we have to change the code, and don't affect the user

	// second, packaging flexibility
	// namespace for cross files, good for compiler
	// we can split our non-member non-friend into different headers, so user just include the one they need,
	// but if these are class members, sorry, the just can be in one file.
	return 0;
}