#include <iostream>
#include <string>
#include <mutex>

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


int main()
{
	// what is exception safe function?
	// when exception throw, 1. don't leak any resource 2. don't let data corrupt
	// for function PrettyMenu::changeBackGround
	// 1. leak resource: if the new Image throw exception, then then unlock will never be executed
	// 2. data corrupt: since already deleted the origin image, when new Image throw exception, the bgImage will be a dangling pointer
	
}