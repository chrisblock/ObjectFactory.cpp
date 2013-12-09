#include "stdafx.h"

#include "ConstructorInjectedImplementation.h"

IMPLEMENT_INSTANTIATOR(ConstructorInjectedImplementation, ITestInterface);

ConstructorInjectedImplementation::ConstructorInjectedImplementation(const std::shared_ptr<ITestInterface> &testInterface) :
	  _testInterface(testInterface)
{
}

ConstructorInjectedImplementation::~ConstructorInjectedImplementation()
{
}

std::shared_ptr<ITestInterface> ConstructorInjectedImplementation::GetTestInterface() const
{
	return _testInterface;
}
