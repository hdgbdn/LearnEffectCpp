#include <iostream>
#include <string>
#include <mutex>
#include <memory>

using namespace std;

class Image
{
public:
	Image(std::istream& imgSrc);
};

class PrettyMenu
{
public:
	void changeBackGround(std::istream& imgSrc);
private:
	mutex mtx;
	Image* bgImage;
	int imageChanges;
};

void PrettyMenu::changeBackGround(std::istream& imgSrc)
{
	mtx.lock();
	delete bgImage;
	++imageChanges;
	bgImage = new Image(imgSrc);
	mtx.unlock();
}

struct Lock
{
	Lock(mutex* m) : pM(m) {}
	shared_ptr<mutex> pM;
};

class PrettyMenuExceptionSafe
{
public:
	void changeBackGround(std::istream& imgSrc);
private:
	mutex mtx;
	shared_ptr<Image> bgImage;
	int imageChanges;
};

void PrettyMenuExceptionSafe::changeBackGround(std::istream& imgSrc)
{
	Lock m1(&mtx);
	bgImage.reset(new Image(imgSrc));		// reset is exception safe
	++imageChanges;
}

struct PMImpl
{
	shared_ptr<Image> bgImage;
	int imageChanges;
};

class PrettyMenuPimpl
{
public:
	void changeBackGround(std::istream& imgSrc);
private:
	mutex mtx;
	shared_ptr<PMImpl> pImpl;
};

void PrettyMenuPimpl::changeBackGround(std::istream& imgSrc)
{
	using std::swap;
	Lock m1(&mtx);
	shared_ptr<PMImpl> pNew = make_shared<PMImpl>(*pImpl);
	pNew->bgImage.reset(new Image(imgSrc));
	++pNew->imageChanges;
	swap(pNew, pImpl);
}


int main()
{
	// what is exception safe function?
	// when exception throw, 1. don't leak any resource 2. don't let data corrupt
	// for function PrettyMenu::changeBackGround
	// 1. leak resource: if the new Image throw exception, then then unlock will never be executed
	// 2. data corrupt: since already deleted the origin image, when new Image throw exception, the bgImage will be a dangling pointer

	// an exception-safe function have one of three guarantee below
	// 1.base: if an exception is thrown, all things remain valid, but the status may be unknown
	// 2.strong: if an exception is thrown, the program's status remain unchanged, it means only two result: success or unchanged
	// 3.nothrow: promise never throw exceptions. the build in types have this guarantee, like pointer, ints etc...

	// and only if your team ask for program to have features like leaking memory or corrupting data during runtime
	// since nothrow is hard to guarantee, because dynamic memory management always have a bad_alloc chance.
	// so what we focus is base or strong
	// and let's look at the changeBackGround and try to make it exception-safe
	// the PrettyMenuExceptionSafe is a base exception safe
	// but we will add a general method: copy and swap, and us pimpl idiom

	// copy-swap don't guarantee the whole function is exception-safe, because if inside function there are other low level exception-safe functions
	// there will be problems. and even the other function is strong guarantee, then won't make it better, because when exception throw,
	// the other function's strong guarantee won't make this function strong guarantee

	// summary:
	// the exception-safe level depends on the lowest one inside the called function, so if your used an non exception-safe function in your function, then your function is non exception-safe
	// when you can write exception safe, then choice the strongest one;
}