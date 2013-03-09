#pragma once

#include <tchar.h>

#include <string>

class Exception
{
public:
	Exception(LPCTSTR message);
	virtual ~Exception();

	std::basic_string<TCHAR> GetExceptionMessage() const;

private:
	std::basic_string<TCHAR> _message;
};
