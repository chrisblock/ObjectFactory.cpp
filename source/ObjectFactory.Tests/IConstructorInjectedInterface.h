#pragma once

class ITestInterface;

class IConstructorInjectedInterface
{
public:
	virtual ~IConstructorInjectedInterface() = default;

	virtual std::shared_ptr<ITestInterface> GetTestInterface() const = 0;
};
