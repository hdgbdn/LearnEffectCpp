#include <iostream>
#include <string>
#include <list>

class Address {};
class Date {};

class Person
{
public:
	Person() {}
private:
	Address address;
	Date brithday;
};

template<class T>
class MySet
{
public:
	bool member(const T& item) const;
	bool insert(const T& item) const;
	void remove(const T& item) const;
	std::size_t size() const;
private:
	std::list<T> rep;
};

template <class T>
bool MySet<T>::member(const T& item) const
{
	return std::find(rep.begin(), rep.end(), item) != rep.end();
}

template <class T>
bool MySet<T>::insert(const T& item) const
{
	if (!member(item)) rep.push_back(item);
}

template <class T>
void MySet<T>::remove(const T& item) const
{
	typename std::list<T>::iterator it = std::find(rep.begin(), rep.end(), item);
	if (it != rep.end()) rep.erase(it);
}

template <class T>
std::size_t MySet<T>::size() const
{
	return rep.size();
}



int main()
{
	// composition is a class contains other class's object as member, like Person, has a Address and a Date;

	// has-a is used in application domain, for non-abstract classes like people, car, image, video
	// is-a is used in abstract domain, like buffers, mutexes, search trees.
	//
	// for example, we want a set data structure in our space sensitive program, the stl version is time sensitive, so we have to implement our own;
	// and we choice the link-list implementation
	// should we inherit std::list? no, public inheritance means "is-a", but set is not a list, such as set's elements are unique, but list can contain duplicate elements
	// so we should use list as a member, "has-a" list
}