#pragma once

#include "ITestInterface.h"

class TestImplementation : public ITestInterface
{
public:
	virtual ~TestImplementation();

	virtual std::string GetString() const;
	virtual void SetString(const char *string);

private:
	std::string _string;
};
