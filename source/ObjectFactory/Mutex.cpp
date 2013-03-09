#include "stdafx.h"

#include "Mutex.h"

Mutex::Mutex(BOOL initialOwn) :
	_handle(__nullptr)
{
	_handle = ::CreateMutex(__nullptr, initialOwn, __nullptr);

	if (_handle == __nullptr)
	{
		// throw
	}
};

Mutex::~Mutex()
{
	::CloseHandle(_handle);
}

HANDLE Mutex::GetRawHandle() const
{
	return _handle;
}
