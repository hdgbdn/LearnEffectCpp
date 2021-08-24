#include <iostream>
#include <string>
#include <chrono>
using namespace std::chrono;

using namespace std;

string getPasswordByName_A(string name)
{
	string pwd;
	if (name == "") throw logic_error("name is empty");
	pwd = "default";
	return pwd;
}

string getPasswordByName_B(string name)
{
	if (name == "") throw logic_error("name is empty");
	string pwd;
	pwd = "default";
	return pwd;
}

string getPasswordByName_C(string name)
{
	if (name == "") throw logic_error("name is empty");
	string pwd("default");
	return pwd;
}

int main()
{
	// see getPasswordByName_A, the pwd variable is no need to define too early, because there is a situation that don't need to return the pwd

	// getPasswordByName_B is a little faster but not enough, it cost a default constructor and a copy assignment

	// getPasswordByName_C is the best implementation, it just cost a copy constructor

	// what about loop?
	const int N = 1000000;
	string test;
	auto start = high_resolution_clock::now();
	for(int i = 0; i < N; ++i)
	{
		test = "i";
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "outside the loop is " << duration.count() << endl;

	start = high_resolution_clock::now();
	for (int i = 0; i < N; ++i)
	{
		string temp("i");
	}
	stop = high_resolution_clock::now();
	cout << "inside the loop is " << duration.count() << endl;

	// first cost a constructor, N copy assignment, a destructor, second cost N constructor and N destructor
	// which one is better? author suggest that only when there is significant performance different, otherwise use the inside one because there is a small scope
	return 0;
}