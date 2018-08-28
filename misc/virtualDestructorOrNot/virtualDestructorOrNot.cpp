/*********************************
This project illustrates that if a base class
is supposed to be inherited by another class, then
the base class must declare its destructor virtual.

Otherwise, the destructor of the derived class will 
not be called if factory pattern is used.

Author: kuwingto
****************************/
#include "stdafx.h"
#include "Header.h"

int main()
{
	{
		CBase_NormalDestructor* pMac = FactoryCreateClassWithNormalDestructor();
		pMac->test();
		delete pMac; // destructor of the derived class will NOT be called.
	}

	{
		CBase_VirtualDestructor* pMac2 = FactoryCreateClassWithVirtualDestructor();
		pMac2->test();
		delete pMac2; // destructor of the derived class will be called.
	}
	
	getchar();
    return 0;
}

