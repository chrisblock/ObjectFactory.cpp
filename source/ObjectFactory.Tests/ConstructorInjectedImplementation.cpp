#include "stdafx.h"

#include "ConstructorInjectedImplementation.h"

IMPLEMENT_INSTANTIATOR(ConstructorInjectedImplementation, ITestInterface);

void swap(ConstructorInjectedImplementation &left, ConstructorInjectedImplementation &right)
{
	using std::swap;

	swap(left._testInterface, right._testInterface);
}

ConstructorInjectedImplementation::ConstructorInjectedImplementation()
{
}

ConstructorInjectedImplementation::ConstructorInjectedImplementation(const std::shared_ptr<ITestInterface> &testInterface) :
	  _testInterface(testInterface)
{
}

ConstructorInjectedImplementation::ConstructorInjectedImplementation(const ConstructorInjectedImplementation &other) :
	  _testInterface(other._testInterface)
{
}

ConstructorInjectedImplementation::ConstructorInjectedImplementation(ConstructorInjectedImplementation &&other) :
	  ConstructorInjectedImplementation()
{
	swap(*this, other);
}

ConstructorInjectedImplementation::~ConstructorInjectedImplementation()
{
}

ConstructorInjectedImplementation &ConstructorInjectedImplementation::operator =(ConstructorInjectedImplementation other)
{
	swap(*this, other);

	return *this;
}


std::shared_ptr<ITestInterface> ConstructorInjectedImplementation::GetTestInterface() const
{
	return _testInterface;
}
