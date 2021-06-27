#include <iostream>

using namespace std;
// bitwise const: a const member function means that it don't change any datamember(non-static)
// logic const: a const member function may change some data member, but it can't be found from outside
// The compiler support bitwise const: a const member shouldn't change even one bit of datamember
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
        textLength = strlen(pText);         // if don't add mutable, we can't change data member in a const memberfunction
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
    const CTextBlock b("hi nihao");
    char* get = &b[0];
    cout << *get << endl;        // "h"
    *get = 'n';
    cout << b[0] << endl;       // although passed compiler, but it can change data member by reference!!

    // function reuse
    // if const and non const version of member function works same, we don't need two sets of codes
    // we use the non const version to call the const version
    // but how to call const version [] in non const version?
    // static_cast<const TextBlock&>(*this) cast *this to const TextBlock&(why reference?)
    // then the const version of [] operator will be called 
    // static_cast<const TextBlock&>(*this)[position] -- calling const version []
    // and ther result is const, so use and only can use const_cast to remove constness

    // why use non const version to call cosnt version
    // because const can be removed, but can't be added
    // if call non const version in const, the non const version may break the constness
    const TextBlock ctxt("nihao");
    TextBlock txt("hi");
    //get = &txt[0];                  // a value of type "const char *" cannot be assigned to an entity of type "char *"
    const char* cp1 = &ctxt[0];     // using const version operator[]
    char* cp2 = &txt[0];            // using const version operator[], both const and non const version is using constversion
    *cp2 = 'n';
    cout << cp2;                    // ni
    // *cc = 'n';                       // expression must be a modifiable lvalue    
}