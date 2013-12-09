#include "stdafx.h"

#include "Lifetimes.h"

std::string Lifetimes::GetName(_In_ Lifetime lifetime)
{
	std::string result;

	switch (lifetime)
	{
	case Lifetimes::Singleton:
		result = "Singleton";
		break;
	case Lifetimes::Thread:
		result = "Thread";
		break;
	case Lifetimes::Transient:
		result = "Transient";
		break;
	default:
		break;
	}

	return result;
}
