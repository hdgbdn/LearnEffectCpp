#include <iostream>
#include <string>

using namespace std;

struct Point
{
	float x;
	float y;
};

struct RectData
{
	Point ulhc;
	Point lrhc;
};

class Rectangle
{
public:
	Point& getUpperLeft() const { return pData->ulhc; }
	Point& getLowerRight() const { return pData->lrhc; }
private:
	shared_ptr<RectData> pData;
};

int main()
{
	// what is a handle?
	// like references, pointer and iterator, return it by const function don't prevent user changing the data it holds
	// like the rectangle class return the Point inside the RectData, but user can change the point data since it's a reference
	// return a const Point& can solve it, but it is still a handle, so don't return handle. But operator[] of container is an exception
	return 0;
}