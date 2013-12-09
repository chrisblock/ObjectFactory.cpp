#include "stdafx.h"

#include "TestImplementation.h"

TestImplementation::~TestImplementation()
{
}

std::string TestImplementation::GetString() const
{
	return _string;
}

void TestImplementation::SetString(const char *string)
{
	_string = string;
}
