#pragma once

#include "IConstructorInjectedInterface.h"

#include <InstantiatorFactory.h>

#include "ITestInterface.h"

class ConstructorInjectedImplementation : public IConstructorInjectedInterface
{
public:
	ConstructorInjectedImplementation(const shared_ptr<ITestInterface> &testInterface);
	virtual ~ConstructorInjectedImplementation();

	virtual shared_ptr<ITestInterface> GetTestInterface() const;

private:
	shared_ptr<ITestInterface> _testInterface;
};

DECLARE_INSTANTIATOR(ConstructorInjectedImplementation);
