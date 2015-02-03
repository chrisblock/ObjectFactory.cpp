#pragma once

#include <string>

class Lifetimes
{
public:
	enum Lifetime
	{
		Singleton,
		Thread,
		Transient
	};

	Lifetimes() = delete;
	Lifetimes(const Lifetimes &other) = delete;
	Lifetimes(Lifetimes &&other) = delete;

	static std::string GetName(_In_ const Lifetime lifetime);
};
