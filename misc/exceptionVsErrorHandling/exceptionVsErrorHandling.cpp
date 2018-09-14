// exceptionVsErrorHandling.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int exception0a()
{
	throw "throw exception0a";
	return 0;
}

int exception0()
{
	exception0a();
	return 0;
}

int exception1a()
{
	throw "throw exception1a";
	return 0;
}

int exception1()
{
	try
	{
		exception1a();
	}
	catch (const char* msg)
	{
		std::cerr << "catch at exception1 " << msg << "\n";
	}
	return 0;
}


int exception2b()
{
	throw "throw exception2b";
	return 0;
}

int exception2a()
{
	exception2b();
	return 0;
}

int exception2()
{
	try
	{
		exception2a();
	}
	catch (const char* msg)
	{
		std::cerr << "catch at exception2 " << msg << "\n";
	}
	return 0;
}

int exception3b()
{
	throw "throw exception3b";
	return 0;
}

int exception3a()
{
	try
	{
		exception3b();
	}
	catch (const char* msg)
	{
		std::cerr << "catch at exception3a " << msg << "\n";
	}
	return 0;
}


int exception3()
{
	try
	{
		exception3a();
	}
	catch (const char* msg)
	{
		std::cerr << "catch at exception3 " << msg << "\n";
	}
	return 0;
}



int exception4a()
{
	int *p = new int[10];
	p[10] = 5;
	delete[] p;
	p = NULL;
	return 0;
}
int exception4()
{
	exception4a();
	/*try
	{
		exception4a();
	}
	catch (const char* msg)
	{
		std::cerr << "catch at exception4 " << msg << "\n";
	}*/
	return 0;
}

int exception5a()
{
	int *p = new int[10];
	delete[] p;
	p = NULL;
	p[5] = 7;
	return 0;
}
int exception5()
{
	try
	{
		exception5a();
	}
	catch (const char* msg)
	{
		std::cerr << "catch at exception5 " << msg << "\n";
	}
	return 0;
}

int exception6a()
{
	int *p = new int[10];
	delete[] p;
	p = NULL;
	std::cout << p[5] << "\n";
	return 0;
}
int exception6()
{
	try
	{
		exception6a();
	}
	catch (const char* msg)
	{
		std::cerr << "catch at exception6 " << msg << "\n";
	}
	return 0;

}
int main()
{
	//exception0();		// cannot run, will terminate program
	exception1();
	exception2();
	exception3();
	//exception4();		// cannot run, will terminate program
	//exception5();		// cannot run, will terminate program
	exception6();		// cannot run, will terminate program
	std::cout << "press key to continue ";
	getchar();
    return 0;
}

