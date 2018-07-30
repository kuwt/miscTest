/*********************************
This project illustrates how to use 
a factory pattern and an interface.

Factory creates a instantiation CClass 
and assigns that to the interface CBase pointer.
****************************/
#include "stdafx.h"
#include "Interface.h"
#include <cstdlib>
int main()
{
	CBase* pMac = FactoryCreate();
	pMac->test();

	system("Pause");
    return 0;
}

