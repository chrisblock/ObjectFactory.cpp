#pragma once

class ITestInterface
{
public:
	virtual ~ITestInterface() = default;

	virtual std::string GetString() const = 0;
	virtual void SetString(const char *string) = 0;
};
