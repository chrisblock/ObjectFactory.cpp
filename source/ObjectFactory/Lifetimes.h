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

	Lifetimes() = delete;
	Lifetimes(const Lifetimes &other) = delete;

	static std::string GetName(_In_ Lifetime lifetime);

private:
	static std::map<Lifetimes::Lifetime, std::string> _lifetimeNames;
};
