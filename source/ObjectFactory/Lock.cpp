#include "stdafx.h"

#include "Lock.h"

Lock::Lock(const Mutex &mutex, ULONG timeoutInMilliseconds) :
	  _handle(mutex.GetRawHandle())
{
	ULONG result = ::WaitForSingleObject(_handle, timeoutInMilliseconds);

	switch (result)
	{
	case WAIT_OBJECT_0:
		break;
	case WAIT_TIMEOUT:
		break;
	case WAIT_FAILED:
		break;
	default:
		break;
	}
}

Lock::~Lock()
{
	::ReleaseMutex(_handle);

	_handle = __nullptr;
}
