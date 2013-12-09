#pragma once

#include "IConstructorInjectedInterface.h"

#include <InstantiatorFactory.h>

class ITestInterface;

class ConstructorInjectedImplementation : public IConstructorInjectedInterface
{
public:
	ConstructorInjectedImplementation(const std::shared_ptr<ITestInterface> &testInterface);
	virtual ~ConstructorInjectedImplementation();

	virtual std::shared_ptr<ITestInterface> GetTestInterface() const;

private:
	std::shared_ptr<ITestInterface> _testInterface;
};

DECLARE_INSTANTIATOR(ConstructorInjectedImplementation);
