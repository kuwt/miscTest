#pragma once

class CBase_NormalDestructor
{

public:
	// attribute
	virtual void test() = 0;

};

class CBase_VirtualDestructor
{
public:
	// destructor
	virtual ~CBase_VirtualDestructor() {};

public:
	// attribute
	virtual void test() = 0;

};

CBase_NormalDestructor* FactoryCreateClassWithNormalDestructor();
CBase_VirtualDestructor* FactoryCreateClassWithVirtualDestructor();