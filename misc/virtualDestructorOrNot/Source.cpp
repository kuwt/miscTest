#include "Header.h"
#include <iostream>

class CClass_NormalDestructor : public CBase_NormalDestructor
{
public:
	CClass_NormalDestructor()
	{
		std::cout << "constructor called. CClass_NormalDestructor." << "\n";
	};
	~CClass_NormalDestructor()
	{
		std::cout << "Destructor called. CClass_NormalDestructor." << "\n";
	};

public:
	void test();
};

class CClass_VirtualDestructor : public CBase_VirtualDestructor
{
public:
	CClass_VirtualDestructor()
	{
		std::cout << "constructor called. CClass_VirtualDestructor" << "\n";
	};
	~CClass_VirtualDestructor()
	{
		std::cout << "Destructor called. CClass_VirtualDestructor" << "\n";
	};

public:
	void test();
};

void CClass_NormalDestructor::test()
{
	std::cout << "test CClass_NormalDestructor" << "\n";
}

void CClass_VirtualDestructor::test()
{
	std::cout << "test CClassVirtualDestructor" << "\n";
}

CBase_NormalDestructor* FactoryCreateClassWithNormalDestructor()
{
	return new CClass_NormalDestructor();
}

CBase_VirtualDestructor* FactoryCreateClassWithVirtualDestructor()
{
	return new CClass_VirtualDestructor();
}
