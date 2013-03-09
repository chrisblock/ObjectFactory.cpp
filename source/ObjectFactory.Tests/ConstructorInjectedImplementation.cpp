#include "stdafx.h"

#include "ConstructorInjectedImplementation.h"

IMPLEMENT_INSTANTIATOR(ConstructorInjectedImplementation, ITestInterface);

ConstructorInjectedImplementation::ConstructorInjectedImplementation(const shared_ptr<ITestInterface> &testInterface) :
	  _testInterface(testInterface)
{
}

ConstructorInjectedImplementation::~ConstructorInjectedImplementation()
{
}

shared_ptr<ITestInterface> ConstructorInjectedImplementation::GetTestInterface() const
{
	return _testInterface;
}
