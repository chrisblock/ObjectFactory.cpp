#pragma once

#include "ITestInterface.h"

class TestImplementation : public ITestInterface
{
public:
	virtual ~TestImplementation();

	virtual basic_string<TCHAR> GetString() const;
	virtual void SetString(LPCTSTR string);

private:
	basic_string<TCHAR> _string;
};
