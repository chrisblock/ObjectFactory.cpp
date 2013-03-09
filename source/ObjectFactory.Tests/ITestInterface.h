#pragma once

class ITestInterface
{
public:
	virtual ~ITestInterface();

	virtual basic_string<TCHAR> GetString() const = 0;
	virtual void SetString(LPCTSTR string) = 0;
};
