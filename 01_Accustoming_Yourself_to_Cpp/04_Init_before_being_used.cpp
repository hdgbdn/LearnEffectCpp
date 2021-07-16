#include <iostream>
#include <list>

using namespace std;

class PhoneNumber{
public:
    PhoneNumber(): num() { cout << "PhoneNumber default constructor being called" << endl; }
    PhoneNumber(const PhoneNumber& n): num(n.num) { cout << "PhoneNumber copy constructor being called" << endl;}
    PhoneNumber& PhoneNumber::operator=(const PhoneNumber& rhs) { 
        cout << "PhoneNumber copy assignment being called" << endl;
        num = rhs.num;
        return *this;
        }
private:
    int num;
};

class ABEntry{
public:
    ABEntry(const string& name, int id, const PhoneNumber& phone){
    	// below is not copy construction, just copy assignment
        theName = name;
        theID = id;
        thePhone = phone;
    }
private:
    string theName;
    int theID;
    PhoneNumber thePhone;
};

class BetterABEntry{
public:
    BetterABEntry(const string& name, int id, const PhoneNumber& phone):
        theName(name), theID(id), thePhone(phone)
        {}
private:
    string theName;
    int theID;
    PhoneNumber thePhone;
};

class A{
public:
    A() {cout << "init A" << endl;}
};

class AA: public A{
public:
    AA() {cout << "init AA" << endl;}
};

class B{
public:
    B() {cout << "init B" << endl;}
};

class C{
public:
    C(): b(), aa(), a() {}
private:
    A a;
    AA aa;
    B b;
};

class ExternClass{
public:
    ExternClass() {cout << "create a extern object" << endl;}
};

ExternClass& func(){
     static ExternClass a;
     return a;
}

// 1. always initialize before use
// 2. always use member initialization list
// 3. non-local static object init order in different compiler unit

int main()
{
    // always initialize objects before using
    // for build-in types, manually initialize:
    int x = 0;
    const char* text = "A C-style string";

    double d;
	// use input stream to initialize
    cin >> d;

    // why recommend to use initialization list not in the function scope?
    // because before entering function scope, members are already initialized,
    // even not write the initialization list, compiler will automatic call the members' default constructor,
    // the "=" in function scope is copy assignment not copy construction
    // see class ABEntry
    PhoneNumber pn = PhoneNumber();
    
    cout << "Test Start: assign in function" << endl;
    ABEntry("jim", 1, pn);
    cout << "Test End: assign in function" << endl;
    // PhoneNumber default constructor being called
    // PhoneNumber copy assignment being called

    cout << "Test Start: copy construct in list" << endl;
    BetterABEntry("jim", 1, pn);
    // PhoneNumber copy constructor being called
    cout << "Test End: copy construct in list" << endl;

    // so, see the difference?

    // in short: always use member initialization list

    // about initialization order
    // class is initialized in the declaration order,
    // no matter what the order is in member initialization list

    // and always base class then the derived

    C c = C();
    // init A
    // init A
    // init AA
    // init B

    // the non-local static object init order in different translation unit

    // if i want to use a extern object defined and init in other files
    // it's impossible to confirm it will be create before or after the time when I use the object

    // so the best is use singleton

    // the resolution is easy: use a local static object returned by a function
    // call the function and the static object is confirmed to be inited
   
    ExternClass a = func();
    ExternClass b = func();
    // a local static variable will only inited once

	// Summary
	// always init object before use
	// for user type, better use member initialization list, than assignment in constructor function
	// if don't use member initialization list, before entering the constructor function, compiler still use members' default constructor
	// so in constructor function, they just assignment, cost more

	// the init order of members are always the declare order, so a array members size data must before the array.

	// use singleton for non-local static object between different compiler unit
	// because we don't know weather it is inited when we use it
    return 0;
}