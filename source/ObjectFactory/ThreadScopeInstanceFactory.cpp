#include "stdafx.h"

#include "ThreadScopeInstanceFactory.h"

#include "IInstantiator.h"

thread_local std::map<std::string, std::shared_ptr<void>> ThreadScopeInstanceFactory::_instances;

void swap(ThreadScopeInstanceFactory &left, ThreadScopeInstanceFactory &right)
{
	using std::swap;

	swap(left._instantiators, right._instantiators);
}

ThreadScopeInstanceFactory::ThreadScopeInstanceFactory()
{
}

ThreadScopeInstanceFactory::ThreadScopeInstanceFactory(const ThreadScopeInstanceFactory &other) :
	  _instantiators(other._instantiators)
{
}

ThreadScopeInstanceFactory::ThreadScopeInstanceFactory(ThreadScopeInstanceFactory &&other) :
	  ThreadScopeInstanceFactory()
{
	swap(*this, other);
}

ThreadScopeInstanceFactory::~ThreadScopeInstanceFactory()
{
	_instantiators.clear();
}

ThreadScopeInstanceFactory &ThreadScopeInstanceFactory::operator =(ThreadScopeInstanceFactory other)
{
	swap(*this, other);

	return *this;
}

void ThreadScopeInstanceFactory::SetCreationStrategy(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator)
{
	_instantiators[interfaceTypeName] = instantiator;
}

std::shared_ptr<void> ThreadScopeInstanceFactory::GetInstance(_In_ const IContainer &container, _In_ const std::string &interfaceTypeName)
{
	std::shared_ptr<void> result;

	std::map<std::string, std::shared_ptr<void>>::const_iterator instance = _instances.find(interfaceTypeName);

	if (instance == _instances.end())
	{
		std::map<std::string, std::shared_ptr<IInstantiator>>::const_iterator instantiator = _instantiators.find(interfaceTypeName);

		if (instantiator == _instantiators.end())
		{
			std::string message(__LOC_A__ "Could not find instantiator for interface '");
			message += interfaceTypeName;
			message += "'.";

			std::exception e(message.c_str());

			throw e;
		}
		else
		{
			std::shared_ptr<IInstantiator> creator = instantiator->second;

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

void ThreadScopeInstanceFactory::RemoveInstance(_In_ const std::string &interfaceTypeName)
{
	_instances.erase(interfaceTypeName);
}

void ThreadScopeInstanceFactory::Remove(_In_ const std::string &interfaceTypeName)
{
	_instances.erase(interfaceTypeName);
	_instantiators.erase(interfaceTypeName);
}
