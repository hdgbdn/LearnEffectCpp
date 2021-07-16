#include <iostream>
#include <vector>

using namespace std;

class Rational
{
public:
    Rational(int v) : val(v) {}
    int val;
};

const Rational operator*(const Rational& lhs, const Rational& rhs){
    Rational ret(lhs.val * rhs.val);
    return ret;
}

class TextBook{
public:
    TextBook(string s = "new book"): text(s) {}
    const char& operator[](size_t position) const { cout << "using const version []" << endl; return text[position]; }
    char& operator[](size_t position) { cout << "using non const version [] " << endl; return text[position]; }
private:
    string text;
};

int main()
{
    // const restrict compiler
    // pointers is a little bit complex
    // const on the left of '*', means the pointed object is constant
    // const on the right of '*', means the pointer itself is constant
    // on both sides, means the pointer and the object pointed to are both constant
    char greeting[] = "Hello";
    char* p1 = greeting;
    const char* p2 = greeting;
    char* const p3 = greeting;
    const char* const p4 = greeting;
    // also, when pointed object is constant, there are two types, both are correct
    auto constPointed = [](const int* i)->int const *{
        return new int(*i);
    };
    int const * val = new int(10);
    const int* ret = constPointed(val);
    cout << *val << endl;       // 10
    cout << *ret << endl;       // 10

    // STL iterator and pointer
    {
        // iterator is base on pointer, like a T*
        // so the const behaviour is same
        vector<int> vec(10, 1);
        const vector<int>::iterator iter = vec.begin();     // the iterator itself is const
        *iter = 20;                                         // correct
        // ++iter;                                          // error: no operator "++" matches these operands -- operand types are: ++ const
        vector<int>::const_iterator cIter = vec.begin();    // the object iterator pointed to is constant
        // cIter = 2;                                       // expression must be a modifiable lvalue
        ++cIter;
    }

    // return a constant ojbect
    {
        Rational a(2), b(3);
        Rational c(4);
        // avoid meanless assignment
        // (a * b) = c;            // no operator "=" matches these operands -- operand types are: const Rational = Rational
    }

    // const member function
    {
        // ! const member can be modified!
        // only if defined a const member function
        // const member function is change this pointer to const pointer, to a pointer point to constant object
        TextBook tb("Hello");
        cout << tb[0] << endl;

        const TextBook ctb("World");
        cout << ctb[0] << endl;

        tb[0] = 'x';        // write to a non const char, correct
        cout << tb[0] << endl;
        // ctb[0] = 'x';    // expression must be a modifiable lvalue

        // if operator returns a non referenced char:
        // tb[0] = 'x' will be error, because try to modify a temp value
    	
    }

    // summary
    // const tell compiler that the object is const, compiler will help you to keep the constness
    // for example: an operator* return const, it help prevents errors like: (a*b)=c
    // pointer: const in left side of '*' is the pointed object const, on the right side of '*' is pointer self const
    // iterator: const vector<int>::iterator and vector<int>::const_iterator.
    return 1;
}