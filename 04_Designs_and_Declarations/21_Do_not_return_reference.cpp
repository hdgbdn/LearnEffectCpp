#include <iostream>
#include <string>

using namespace std;

#define STACK_STATIC

class Rational
{
	friend const Rational& operator*(const Rational&, const Rational&);
	friend  bool operator==(const Rational&, const Rational&);
public:
	Rational(int numerator = 0, int denominator = 1): n(numerator), d(denominator){}
private:
	int n, d;
};

const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
#ifdef STACK
	Rational result(lhs.n * rhs.n, lhs.d * rhs.d);
	return result;
#endif

#ifdef HEAP
	Rational* result = new Rational(lhs.n * rhs.n, lhs.d * rhs.d);
	return *result;
#endif

#ifdef STACK_STATIC
	static Rational result(lhs.n * rhs.n, lhs.d * rhs.d);
	return result;
#endif
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
	if (lhs.n == rhs.n && lhs.d == rhs.d) return true;
	return false;
}

int main()
{
	// see class above, if we want to return a reference, remember, a reverence is always a alias, we need to know the real object
	// since we have to create the object, then we have 2 choice: in stack or in heap
	// let's see in stack
	// returned a local object, will cause undefined behaviour, because after leaving the scope, the reference is pointing to a deleted memory

	// let's see in heap
	// now reference is pointing to a valid object, but, how to delete the object? since we permanently lose the pointer
	Rational x, y, z, w;
	w = x * y * z;		// we lost the pointer, memory leak warning

	// ok, there are even more bad idea, using static to avoid the local problem
	{
		Rational a(1, 2);
		Rational b(3, 4);
		Rational c(5, 6);
		cout << (a * b == b * c) << endl;
		// the answer is 1, because the references are pointing to the same static object
	}

	// what is the right operation?
	// just return the object, let the compiler will do the optimization
	return 0;
}