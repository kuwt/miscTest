#include "Header.h"
#include "Interface.h"

CBase* FactoryCreate()
{
	return new CClass();
}