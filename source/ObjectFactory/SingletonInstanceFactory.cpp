#include "stdafx.h"

#include "SingletonInstanceFactory.h"

#include "IInstantiator.h"

SingletonInstanceFactory::SingletonInstanceFactory() :
	  _mutex()
{
}

SingletonInstanceFactory::~SingletonInstanceFactory()
{
	std::unique_lock<std::recursive_mutex> lock(_mutex);

	_instances.clear();

	_instantiators.clear();
}

void SingletonInstanceFactory::SetCreationStrategy(_In_z_ const char *interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator)
{
	_instantiators[interfaceTypeName] = instantiator;
}

std::shared_ptr<void> SingletonInstanceFactory::GetInstance(_In_ const IContainer &container, _In_z_ const char *interfaceTypeName)
{
	std::shared_ptr<void> result;

	std::unique_lock<std::recursive_mutex> lock(_mutex);

	auto instance = _instances.find(interfaceTypeName);

	if (instance == _instances.end())
	{
		auto instantiator = _instantiators.find(interfaceTypeName);

		if (instantiator == _instantiators.end())
		{
			std::string message(__LOC_A__ " Could not find instantiator for interface '");
			message += interfaceTypeName;
			message += "'.";

			std::exception e(message.c_str());

			throw e;
		}
		else
		{
			auto creator = instantiator->second;

			result = creator->CreateInstance(container);

			_instances[interfaceTypeName] = result;
		}
	}
	else
	{
		result = instance->second;
	}

	return result;
}

void SingletonInstanceFactory::RemoveInstance(_In_z_ const char *interfaceTypeName)
{
	std::unique_lock<std::recursive_mutex> lock(_mutex);

	_instances.erase(interfaceTypeName);
}

void SingletonInstanceFactory::Remove(_In_z_ const char *interfaceTypeName)
{
	std::unique_lock<std::recursive_mutex> lock(_mutex);

	_instances.erase(interfaceTypeName);
	_instantiators.erase(interfaceTypeName);
}

int SingletonInstanceFactory::GetNumberOfInstances() const
{
	return _instances.size();
}
