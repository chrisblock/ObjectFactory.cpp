#pragma once

class Mutex
{
public:
	Mutex(BOOL initialOwn = FALSE);
	~Mutex();

	HANDLE GetRawHandle() const;

private:
	HANDLE _handle;

	Mutex(const Mutex &other);
	Mutex &operator =(const Mutex &other);
};
