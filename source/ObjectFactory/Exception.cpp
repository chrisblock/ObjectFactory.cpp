#include "stdafx.h"

#include "Exception.h"

Exception::Exception(LPCTSTR message) :
	  _message(message)
{
}

Exception::~Exception()
{
}

basic_string<TCHAR> Exception::GetExceptionMessage() const
{
	return _message;
}
