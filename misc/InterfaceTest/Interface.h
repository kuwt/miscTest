#pragma once
class CBase
{
public:
	// destructor
	virtual ~CBase() {};

public:
	// attribute
	virtual void test() = 0;

};

CBase* FactoryCreate();