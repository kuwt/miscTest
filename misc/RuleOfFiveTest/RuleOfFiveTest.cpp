// RuleOfFiveTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


struct resource
{
	int x = 0;
};

class foo
{
public:
	// constructor
	foo()
		: p{ new resource{} }
	{ }

	// copy constructor
	foo(const foo& other)
		: p{ new resource{ *(other.p) } }
	{ }

	// move constructor
	foo(foo&& other)
		: p{ other.p }
	{
		other.p = nullptr;
	}

	// assignment operator
	foo& operator=(const foo& other)
	{
		if (&other != this) {
			delete p;
			p = nullptr;
			p = new resource{ *(other.p) };
		}
		return *this;
	}

	// move assignment operator
	foo& operator=(foo&& other)
	{
		if (&other != this) {
			delete p;
			p = other.p;
			other.p = nullptr;
		}
		return *this;
	}
	~foo()
	{
		delete p;
	}
private:
	resource* p = NULL;
};




int main()
{

    return 0;
}

