#include "stdafx.h"

#include "SingletonInstanceFactory.h"

#include "IInstantiator.h"

void swap(SingletonInstanceFactory &left, SingletonInstanceFactory &right)
{
	using std::swap;

	std::lock(left._mutex, right._mutex);

	std::lock_guard<std::recursive_mutex> l(left._mutex, std::adopt_lock);
	std::lock_guard<std::recursive_mutex> r(right._mutex, std::adopt_lock);

	swap(left._instances, right._instances);
	swap(left._instantiators, right._instantiators);
}

SingletonInstanceFactory::SingletonInstanceFactory() :
	  _mutex()
{
}

SingletonInstanceFactory::SingletonInstanceFactory(SingletonInstanceFactory &&other) :
	  SingletonInstanceFactory()
{
	swap(*this, other);
}

SingletonInstanceFactory::SingletonInstanceFactory(const SingletonInstanceFactory &other)
{
	std::lock_guard<std::recursive_mutex> lock(other._mutex);

	_instances = other._instances;
	_instantiators = other._instantiators;
}

SingletonInstanceFactory::~SingletonInstanceFactory()
{
	std::lock_guard<std::recursive_mutex> lock(_mutex);

	_instances.clear();

	_instantiators.clear();
}

SingletonInstanceFactory &SingletonInstanceFactory::operator = (SingletonInstanceFactory other)
{
	std::lock_guard<std::recursive_mutex> lock(_mutex);

	swap(*this, other);

	return *this;
}

void SingletonInstanceFactory::SetCreationStrategy(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator)
{
	_instantiators[interfaceTypeName] = instantiator;
}

std::shared_ptr<void> SingletonInstanceFactory::GetInstance(_In_ const IContainer &container, _In_ const std::string &interfaceTypeName)
{
	std::shared_ptr<void> result;

	std::lock_guard<std::recursive_mutex> lock(_mutex);

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

void SingletonInstanceFactory::RemoveInstance(_In_ const std::string &interfaceTypeName)
{
	std::lock_guard<std::recursive_mutex> lock(_mutex);

	_instances.erase(interfaceTypeName);
}

void SingletonInstanceFactory::Remove(_In_ const std::string &interfaceTypeName)
{
	std::lock_guard<std::recursive_mutex> lock(_mutex);

	_instances.erase(interfaceTypeName);
	_instantiators.erase(interfaceTypeName);
}

int SingletonInstanceFactory::GetNumberOfInstances() const
{
	return _instances.size();
}
