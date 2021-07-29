#include <iostream>
#include <string>

class RationalMember
{
public:
	RationalMember(int numerator = 0, int denominator = 1) {};
	const RationalMember operator*(const RationalMember& rhs)
	{
		return RationalMember(1, 2);
	};
};

class RationalNonMember
{
public:
	RationalNonMember(int numerator = 0, int denominator = 1) {};
};

const RationalNonMember operator*(const RationalNonMember&, const RationalNonMember&)
{
	return RationalNonMember(1, 2);
}

int main()
{
	// class: RationalMember, if we want implicit conversation for a int
	RationalMember oneHalf(1, 2);
	RationalMember result = oneHalf * 2;				// seems ok
	// result = 2 * oneHalf;		// binary '*': no global operator found which takes type 'RationalMember' (or there is no acceptable conversion)
	// why? because a member operator function's lhs type is a explicit *this type
	// so use non-member version:
	RationalNonMember oneFourth(1, 4);
	RationalNonMember result2 = oneFourth * 2;				// ok
	result2 = 2 * oneFourth;								// ok
	return 0;
}