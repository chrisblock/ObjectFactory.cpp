#include "stdafx.h"

#include "TransientInstanceFactory.h"

#include "IInstantiator.h"

TransientInstanceFactory::TransientInstanceFactory()
{
}

TransientInstanceFactory::~TransientInstanceFactory()
{
	_instantiators.clear();
}

void TransientInstanceFactory::SetCreationStrategy(_In_z_ LPCSTR interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator)
{
	_instantiators[interfaceTypeName] = instantiator;
}

std::shared_ptr<void> TransientInstanceFactory::GetInstance(_In_ const IContainer &container, _In_z_ LPCSTR interfaceTypeName)
{
	std::shared_ptr<void> result;

	auto instantiator = _instantiators.find(interfaceTypeName);

	if (instantiator == _instantiators.end())
	{
		std::string message(__LOC_A__ "Could not find instance creator for interface '");
		message += interfaceTypeName;
		message += "'.";

		std::exception e(message.c_str());

		throw e;
	}
	else
	{
		auto creator = instantiator->second;

		result = creator->CreateInstance(container);
	}

	return result;
}

void TransientInstanceFactory::RemoveInstance(_In_z_ LPCSTR interfaceTypeName)
{
	UNREFERENCED_PARAMETER(interfaceTypeName);

	// this method does nothing here because this instance factory does not keep track of instances it has created
}

void TransientInstanceFactory::Remove(_In_z_ LPCSTR interfaceTypeName)
{
	_instantiators.erase(interfaceTypeName);
}
