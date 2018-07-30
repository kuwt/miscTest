// ClassFunctionPointerTest.cpp : Defines the entry point for the console application.
//


#include <string>
#include <iostream>
class A
{
private:
	std::string m_str;
public:
	A(std::string str)
	{
		m_str = str;
	}

	void printing()
	{
		std::cout << m_str;
	}
};


int main()
{
	A obj1("abc");
	A obj2("def");

	typedef void (A::*FUNC) ();
	FUNC f = &A::printing;

	(obj1.*f)();
	(obj2.*f)();
	

	getchar();
    return 0;
}

