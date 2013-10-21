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

	static std::string GetName(_In_ Lifetime lifetime);

private:
	static std::map<Lifetime, std::string> _lifetimeNames;

	Lifetimes();
	Lifetimes(const Lifetimes &other);
};
