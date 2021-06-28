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
    // for build-in types, mannualy initilize:
    int x = 0;
    const char* text = "A C-style string";

    double d;
    cin >> d;

    // for anything else, use constructor to make sure
    // every constructor initialize every member
    // and better in member initialization list, not in function
    // because even not write the initialization list, compiler
    // will automaticly call the members' default constructor,
    // before enter the function, so in function, they will be assign again,
    // not copy construct
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

    // about initiliazation order
    // class is initialized in the declaration order, no matter what the order is
    // in member initialization list
    // and always base class the derived

    C c = C();
    // init A
    // init A
    // init AA
    // init B

    // the non-local static object init order in different compiler unit

    // if i want to use a extern object defined and init in other files
    // it's impossible to confirm it will be create before or after the time when
    // I use the object
    // so the best is use singleton

    // the resolution is easy: use a local static object returned by a function
    // call the function and the static object is confirmed to be inited
   
    ExternClass a = func();
    ExternClass b = func();
    // a local static variable will only inited once
    return 0;
}