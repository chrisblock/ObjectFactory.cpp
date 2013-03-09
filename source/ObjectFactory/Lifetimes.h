#pragma once

#include <tchar.h>

#include <string>
#include <map>

class Lifetimes
{
public:
	enum Lifetime
	{
		Singleton,
		Transient,
		Thread
	};

	static std::basic_string<TCHAR> GetName(Lifetime lifetime);

private:
	static std::map<Lifetime, std::basic_string<TCHAR>> _lifetimeNames;

	Lifetimes();
};
