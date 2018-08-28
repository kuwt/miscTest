/**
RuleOfFiveTest.cpp
Purpose: Illustrate the Rule of Five for class design
and how the calling pattern will invoke each of the rule of five methods

@author kuwingto
@version 1.0 23/08/2018
*/
#include "stdafx.h"
#include <iostream>

struct resource
{
	int x = 0;
};

class foo
{
public:
	// constructor
	foo()
	{
		std::cout << "constructor" << "\n";
		p = new resource();
	}

	// copy constructor
	foo(const foo& other)
	{ 
		std::cout << "copy constructor" << "\n";
		p = new resource(*(other.p));
	}

	// move constructor
	foo(foo&& other)
	{
		std::cout << "move constructor" << "\n";
		p = other.p;
		other.p = nullptr;
	}

	// assignment operator
	foo& operator=(const foo& other)
	{
		std::cout << "assignment operator" << "\n";
		if (&other != this)
		{
			delete p;
			p = nullptr;
			p = new resource{ *(other.p) };
		}
		return *this;
	}

	// move assignment operator
	foo& operator=(foo&& other)
	{
		std::cout << "move assignment operator" << "\n";
		if (&other != this) 
		{
			delete p;
			p = other.p;
			other.p = nullptr;
		}
		return *this;
	}
	// destructor
	~foo()
	{
		std::cout << "destructor" << "\n";
		delete p;
	}
private:
	resource* p = NULL;
};


int main()
{
	foo st1;   
	foo st2(st1);   // copy constructor
	foo st3 = st1;   // copy constructor

	foo st4;
	st4 = foo();    // move assignment operator

	foo st5;
	foo st6(std::move(st5));  // move constructor

	foo st7;
	foo st8;
	st8 = st7;  // assignment operator
    return 0;
}

