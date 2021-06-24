#include <iostream>

using namespace std;

#define ASPECT_RATIO 1.653
const double AspectRatio = 1.653;
char* const constPointerAuthorName("Scoot Meyers");
const char* constCharAuthorName("Scoot Meyers");
const char* const authorName("Scoot Meyers");

class GamePlayer{
public:
    static const int NumTurns = 5;      // declar a const, remember it's declaration not defination, declaraion can assign value? yes!
    // 
    int scores[NumTurns];               // use constant
};

// enum hack
// use enum as ints
class EnumHack{
private:
    enum
    {
        NumTurns = 5
    };
    int scores[NumTurns];
};

int main()
{   
    // why use const instead of marco?
    // 1. symbol tracing
    // *about constant pointers replacement
    constPointerAuthorName[0];            // char* const: can change memory value
    // constCharAuthorName = new char('a');     // char* const: can't change pointer self
    // constCharAuthorName[0] = 'a';            // const char*: expression must be a modifiable lvalue
    constCharAuthorName = new char('a');        // const char*: can change pointer self
    // authorName[0] = 'a';                     // const char* const: expression must be a modifiable lvalue
    // authorName = new char('a');              // const char* const: expression must be a modifiable lvalue

    // 2. scope
    // can't limit marcro's scope inside a specified class
    cout << 1 << endl;;
    cout << GamePlayer::NumTurns << endl;

    // macros
    #define CALL_WITH_MAX(a, b) ((a) > (b) ? (a) : (b))
    int a = 5, b = 0;
    CALL_WITH_MAX(++a, b);          // a ++ twice, because ++a > b, so return (a) = (++a), twice
    CALL_WITH_MAX(++a, b + 10);     // a ++ once, because ++a < b, return b
    return 0;
}