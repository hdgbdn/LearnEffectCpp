#include <iostream>
#include <string>

using namespace std;

// if you want house is uncopiable
// then what you should do?
// in old time when the book wrote, we achieve this by declaring copy control functions private
// because if you don't declar one, compiler will ceclar their version

// but a little bit complex
// first declar a uncopyable class
class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

// private can't be accessed
class HomeForSale: private Uncopyable{

};

// in new standrad, use =delete
class NewUncopyable{
protected:
    NewUncopyable() {}
    ~NewUncopyable() {}
    NewUncopyable(const NewUncopyable&) = delete;
    NewUncopyable& operator=(const NewUncopyable&) = delete;
};

class NewHomeForSale: private NewUncopyable{

};

int main()
{
    HomeForSale myHome;
    // HomeForSale hisHome(myHome);        // error: a deleted function
    NewHomeForSale myNewHome;
    // NewHomeForSale hisHome(myNewHome);  // error: a deleted function 
}