#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

void lock(mutex* pm);
void unlock(mutex* pm);

class Lock
{
public:
	explicit Lock(mutex* pm) : mutexPtr(pm) { lock(mutexPtr); }
	~Lock() { unlock(mutexPtr); }
private:
	mutex* mutexPtr;
};

int main()
{
	Lock ml1 (new mutex());
	Lock ml2(ml1);

	// now we use a RAII object: Lock to hold the resource and manage it by construction and destruction.
	// but what happens when copying it?

	// 1: prevent copy
	// 2: use shared_ptr to add use_count

	// and some alternate ways:
	// 3: deep copy the managed resources
	// 4: some times need only on RAII holds the raw resources, use unique_ptr.

	// if you want to keep the raw resource after the smart pointer use count decrease to 0, you can define your own deleter;
}