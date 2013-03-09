#include "stdafx.h"

#include "Lifetimes.h"

#define DEFINE_LIFETIME_MAP(x) _lifetimeNames[x] = basic_string<TCHAR>(_STR2WSTR(STRINGIFY(x)));

std::map<Lifetimes::Lifetime, std::basic_string<TCHAR>> Lifetimes::_lifetimeNames;

Lifetimes::Lifetimes()
{
}

basic_string<TCHAR> Lifetimes::GetName(Lifetime lifetime)
{
	if (_lifetimeNames.size() == 0)
	{
		DEFINE_LIFETIME_MAP(Lifetimes::Singleton);
		DEFINE_LIFETIME_MAP(Lifetimes::Transient);
		DEFINE_LIFETIME_MAP(Lifetimes::Thread);
	}

	return _lifetimeNames[lifetime];
}
