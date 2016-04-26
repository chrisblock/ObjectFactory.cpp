#pragma once

#include "ITestInterface.h"

class TestImplementation : public ITestInterface
{
public:
	TestImplementation();
	TestImplementation(const TestImplementation &other);
	TestImplementation(TestImplementation &&other);
	virtual ~TestImplementation();

	TestImplementation &operator =(TestImplementation other);

	friend void swap(TestImplementation &left, TestImplementation &right);

	virtual std::string GetString() const override;
	virtual void SetString(const char *string) override;

private:
	std::string _string;
};

void swap(TestImplementation &left, TestImplementation &right);
