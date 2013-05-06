#include "stdafx.h"

#include "SingletonInstanceFactory.h"

#include "Exception.h"
#include "Lock.h"

SingletonInstanceFactory::SingletonInstanceFactory() :
	  _mutex(FALSE)
{
}

SingletonInstanceFactory::~SingletonInstanceFactory()
{
	_instances.clear();

	_instantiators.clear();
}

void SingletonInstanceFactory::SetCreationStrategy(LPCTSTR interfaceTypeName, const shared_ptr<IInstantiator> &instantiator)
{
	_instantiators[interfaceTypeName] = instantiator;
}

shared_ptr<void> SingletonInstanceFactory::GetInstance(const IContainer &container, LPCTSTR interfaceTypeName)
{
	shared_ptr<void> result;

	Lock lock(_mutex);

	auto instance = _instances.find(interfaceTypeName);

	if (instance == _instances.end())
	{
		auto instantiator = _instantiators.find(interfaceTypeName);

		if (instantiator == _instantiators.end())
		{
			basic_string<TCHAR> message(__LOC__ _T("Could not find instantiator for interface '"));
			message += interfaceTypeName;
			message += _T("'.");

			throw new Exception(message.c_str());
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

void SingletonInstanceFactory::Remove(LPCTSTR interfaceTypeName)
{
	Lock lock(_mutex);

	_instances.erase(interfaceTypeName);
	_instantiators.erase(interfaceTypeName);
}

int SingletonInstanceFactory::GetNumberOfInstances() const
{
	return _instances.size();
}
