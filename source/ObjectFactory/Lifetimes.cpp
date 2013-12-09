#include "stdafx.h"

#include "Lifetimes.h"

#define DEFINE_LIFETIME_MAP(x) _lifetimeNames[x] = std::string(STRINGIFY(x));

std::map<Lifetimes::Lifetime, std::string> Lifetimes::_lifetimeNames;

std::string Lifetimes::GetName(_In_ Lifetime lifetime)
{
	if (_lifetimeNames.size() == 0)
	{
		DEFINE_LIFETIME_MAP(Lifetimes::Singleton);
		DEFINE_LIFETIME_MAP(Lifetimes::Transient);
		DEFINE_LIFETIME_MAP(Lifetimes::Thread);
	}

	return _lifetimeNames[lifetime];
}
