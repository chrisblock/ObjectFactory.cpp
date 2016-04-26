#include "stdafx.h"

#include "TestImplementation.h"

void swap(TestImplementation &left, TestImplementation &right)
{
	using std::swap;

	swap(left._string, right._string);
}

TestImplementation::TestImplementation()
{
}

TestImplementation::TestImplementation(const TestImplementation &other) :
	  _string(other._string)
{
}

TestImplementation::TestImplementation(TestImplementation &&other) :
	  TestImplementation()
{
	swap(*this, other);
}

TestImplementation::~TestImplementation()
{
}

TestImplementation &TestImplementation::operator =(TestImplementation other)
{
	swap(*this, other);
	return *this;
}

std::string TestImplementation::GetString() const
{
	return _string;
}

void TestImplementation::SetString(const char *string)
{
	_string = string;
}
