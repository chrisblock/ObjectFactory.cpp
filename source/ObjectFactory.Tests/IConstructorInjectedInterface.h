#pragma once

#include "ITestInterface.h"

class IConstructorInjectedInterface
{
public:
	virtual ~IConstructorInjectedInterface();

	virtual shared_ptr<ITestInterface> GetTestInterface() const = 0;
};
