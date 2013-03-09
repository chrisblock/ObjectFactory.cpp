#include "stdafx.h"

#include "TestImplementation.h"

TestImplementation::~TestImplementation()
{
}

basic_string<TCHAR> TestImplementation::GetString() const
{
	return _string;
}

void TestImplementation::SetString(LPCTSTR string)
{
	_string = string;
}
