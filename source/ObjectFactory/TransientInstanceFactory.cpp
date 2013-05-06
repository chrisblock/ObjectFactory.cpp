#include "stdafx.h"

#include "TransientInstanceFactory.h"

#include "Exception.h"

TransientInstanceFactory::~TransientInstanceFactory()
{
	_instantiators.clear();
}

void TransientInstanceFactory::SetCreationStrategy(LPCTSTR interfaceTypeName, const shared_ptr<IInstantiator> &instantiator)
{
	_instantiators[interfaceTypeName] = instantiator;
}

shared_ptr<void> TransientInstanceFactory::GetInstance(const IContainer &container, LPCTSTR interfaceTypeName)
{
	shared_ptr<void> result;

	auto instantiator = _instantiators.find(interfaceTypeName);

	if (instantiator == _instantiators.end())
	{
		basic_string<TCHAR> message(__LOC__ _T("Could not find instance creator for interface '"));
		message += interfaceTypeName;
		message += _T("'.");

		throw new Exception(message.c_str());
	}
	else
	{
		auto creator = instantiator->second;

		result = creator->CreateInstance(container);
	}

	return result;
}

void TransientInstanceFactory::Remove(LPCTSTR interfaceTypeName)
{
	_instantiators.erase(interfaceTypeName);
}
