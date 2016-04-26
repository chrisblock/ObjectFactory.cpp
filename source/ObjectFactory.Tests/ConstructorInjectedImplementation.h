#pragma once

#include "IConstructorInjectedInterface.h"

#include <InstantiatorFactory.h>

class ITestInterface;

class ConstructorInjectedImplementation : public IConstructorInjectedInterface
{
public:
	ConstructorInjectedImplementation();
	ConstructorInjectedImplementation(const std::shared_ptr<ITestInterface> &testInterface);
	ConstructorInjectedImplementation(const ConstructorInjectedImplementation &other);
	ConstructorInjectedImplementation(ConstructorInjectedImplementation &&other);
	virtual ~ConstructorInjectedImplementation();

	ConstructorInjectedImplementation &operator =(ConstructorInjectedImplementation other);

	friend void swap(ConstructorInjectedImplementation &left, ConstructorInjectedImplementation &right);

	virtual std::shared_ptr<ITestInterface> GetTestInterface() const override;

private:
	std::shared_ptr<ITestInterface> _testInterface;
};

void swap(ConstructorInjectedImplementation &left, ConstructorInjectedImplementation &right);

DECLARE_INSTANTIATOR(ConstructorInjectedImplementation);
