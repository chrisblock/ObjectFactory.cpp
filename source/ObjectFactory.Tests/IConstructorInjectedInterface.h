#pragma once

class ITestInterface;

class IConstructorInjectedInterface
{
public:
	virtual ~IConstructorInjectedInterface();

	virtual std::shared_ptr<ITestInterface> GetTestInterface() const = 0;
};
