#include <iostream>
#include <string>
#include <functional>


//--------------------------NVI
class GameCharacter
{
public:
	virtual int healthValue() const {}
};

class NVIGameCharacter
{
public:
	int healthValue() const
	{
		// do something before
		int retVal = doHealthValue();
		// do something after
		return retVal;
	}
private:
	virtual int doHealthValue() const { return 0; }
};

//--------------------------function pointer
class PointerGameCharacter;
int defaultHealthCalc(const PointerGameCharacter&) { return 0; }
int customHealthCalc(const PointerGameCharacter&) { return 1; }
class PointerGameCharacter
{
	using HealthCalcFunc = int(*)(const PointerGameCharacter&);
public:
	PointerGameCharacter(HealthCalcFunc hcf = defaultHealthCalc):func(hcf) {}
	int healtheValue() const { return func(*this); }
	void setHealthCalcFunc(HealthCalcFunc f) { func = f; }
private:
	HealthCalcFunc func;
};

//--------------------------std::function
class FunctionGameCharacter;

double functionType(const FunctionGameCharacter&) { return 0; }

struct structType
{
	float operator()(const FunctionGameCharacter&) { return 1; }
};

class classType
{
public:
	int classHealthMember(const FunctionGameCharacter&) const { return 2; }
};

class FunctionGameCharacter
{
	using HealthCalcFunc = std::function<int(const FunctionGameCharacter&)>;
public:
	FunctionGameCharacter(HealthCalcFunc hcf = functionType): func(hcf) {}
	int healtheValue() const { return func(*this); }
	void setHealthCalcFunc(HealthCalcFunc f) { func = f; }
private:
	HealthCalcFunc func;
};


//--------------------------Strategy
class StrategyGameCharacter;
class StrategyCalcFuncBase
{
public:
	virtual int calc(const StrategyGameCharacter& gc) const { return 0; }
};

class StrategyCalcFuncDerived: public StrategyCalcFuncBase
{
public:
	int calc(const StrategyGameCharacter& gc) const override { return 1; }
};

StrategyCalcFuncBase defaultStrategyCalcFuncBase;

class StrategyGameCharacter
{
public:
	StrategyGameCharacter(StrategyCalcFuncBase* p = &defaultStrategyCalcFuncBase): func(p) {}
	int healtheValue() const { return func->calc(*this); }
	void setHealthCalcFunc(StrategyCalcFuncBase* p) { func = p; }
private:
	StrategyCalcFuncBase* func;
};



int main()
{
	// think about a game, characters need a health system, so we first come out a virtual function
	// so it's a impure virtual function, means it has a default implementation
	// but let's see something other than virtual function

	// Non-Virtual Interface for Template Method
	// it wraps the implementation into a public non virtual function, the doHealthValue itself is a virtual function
	// the benefit is the do something before and do something after, you can do extra thing such as log, clear resource, lock mutex etc..

	// Function Pointers for Strategy pattern
	PointerGameCharacter orge1;
	// can assign different functions among same class objects
	PointerGameCharacter orge2(customHealthCalc);
	std::cout << "orge1 health is " << orge1.healtheValue() << std::endl;
	std::cout << "orge2 health is " << orge2.healtheValue() << std::endl;
	// also can be changed in runtime
	orge1.setHealthCalcFunc(customHealthCalc);
	std::cout << "orge1 health after set to custom is " << orge1.healtheValue() << std::endl;
	// but the flexibility comes from the fact that the function don't belong to the inheritance system,
	// so it brings the con that the function can only access the public part of the class

	// introducing std::function
	FunctionGameCharacter human;
	std::cout << "default human health: " << human.healtheValue() << std::endl;
	// can return different type(if implicit convert is possible)
	human.setHealthCalcFunc(structType());
	std::cout << "struct type human health: " << human.healtheValue() << std::endl;
	human.setHealthCalcFunc(std::bind(&classType::classHealthMember, classType(), std::placeholders::_1));
	std::cout << "class type human health: " << human.healtheValue() << std::endl;

	// strategy pattern
	StrategyGameCharacter devil;
	std::cout << "devil default health: " << devil.healtheValue() << std::endl;
	devil.setHealthCalcFunc(new StrategyCalcFuncDerived());
	std::cout << "devil derived health: " << devil.healtheValue() << std::endl;

}