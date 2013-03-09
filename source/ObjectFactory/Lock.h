#pragma once

#include "Mutex.h"

class Lock
{
public:
	Lock(const Mutex &mutex, ULONG timeoutInMilliseconds = INFINITE);
	~Lock();

private:
	HANDLE _handle;

	Lock(const Lock &other);
	Lock &operator =(const Lock &other);
};
