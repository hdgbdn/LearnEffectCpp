#include <iostream>
#include <vector>

using namespace std;
// bitwise const: a const member function means that it don't change any data member(non-static)
// logic const: a const member function may change some data member, but it can't be found from outside
// The compiler support bitwise const: a const member shouldn't change even one bit of data member
// but some time we need to change some member, so here come keyword: mutable

class CTextBlock{
public:
    CTextBlock(const char* c){
        pText = (char*)malloc(strlen(c) + 1); 
        strcpy(pText, c);
        cout << "created " << pText << endl;
    }
    char& operator[](size_t position) { return pText[position]; }
    char& operator[](size_t position) const{ return pText[position]; }
    size_t length() const;
private:
    char* pText;
    // add some data to cache length
    mutable size_t textLength;
    mutable bool lengthIsValid;
};

size_t CTextBlock::length() const
{
    if(!lengthIsValid){
        textLength = strlen(pText);         // if don't add mutable, we can't change data member in a const member function
        lengthIsValid = true;               // expression must be a modifiable lvalue
    }
    return textLength;
}

class TextBlock{
public:
    TextBlock(const char *c)
    {
        pText = (char *)malloc(strlen(c) + 1);
        strcpy(pText, c);
        cout << "created " << pText << endl;
    }
    const char& operator[](size_t position) const{
        // some common operations in both const and non const
        cout << "using const version operator[]" << endl;
        return pText[position];
    }
    char& operator[](size_t position){
        return
            const_cast<char&>(
                static_cast<const TextBlock&>(*this)[position]
            );
    }
private:
    char *pText;
};

int main()
{
	// bitwise vs logical constness
	// look below, although it's bitwise const, we still can change the object's array element
    const CTextBlock b("hi nihao");
    char* get = &b[0];
    cout << *get << endl;        // "h"
    *get = 'n';
    cout << b[0] << endl;       // although passed compiler, but it can change data member by reference!!
    
    // if const and non const version of member function works same, we don't need two sets of codes
    // we use the non const version to call the const version
    // why not const version to call non const? because non const version may have change some member, can't ensure const
    // but non const to call const, just remove the const, the const will works as well as non const.
    // but how to call const version [] in non const version?
    // static_cast<const TextBlock&>(*this) cast *this to const TextBlock&
    // then the const version of [] operator will be called 
    // static_cast<const TextBlock&>(*this)[position] -- calling const version []
    // and the result is const, so use and only can use const_cast to remove const


    // const iterator
    vector<int> vec{ 1, 2, 3, 4, 5 };
    const vector<int>::iterator iter = vec.begin();     // guess is iter const or *iter const
    *iter = 2;
    // iter++;          // error, const iterator
    vector<int>::const_iterator citer = vec.begin();
    citer++;
    // *citer = 2;      // error, point to const

    // why use non const version to call const version
    // because const can be removed, but can't be added
    // if call non const version in const, the non const version may break the const
    const TextBlock ctxt("nihao");
    TextBlock txt("hi");
    //get = &txt[0];                  // a value of type "const char *" cannot be assigned to an entity of type "char *"
    const char* cp1 = &ctxt[0];     // using const version operator[]
    char* cp2 = &txt[0];            // using const version operator[], both const and non const version is using const version
    *cp2 = 'n';
    cout << cp2;                    // ni
    // *cc = 'n';                       // expression must be a modifiable lvalue

	// summary
	// const member function: can call this function by const object. It tells user it won't change object self, and can operate const object
	// bitwise vs logical: bitwise is the C++ definition of constness, but has some leak, such as modify element in an array, because element is not the member of class
	// logical constness thinks can modify some data member when users can't notice. keyword mutable.
	// any we can reuse the same function with only constness difference, by using cast.

}