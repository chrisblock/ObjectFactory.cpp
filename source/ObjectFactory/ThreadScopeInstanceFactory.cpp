#include "stdafx.h"

#include "ThreadScopeInstanceFactory.h"

#include <thread>

#include "IInstantiator.h"

std::map<std::thread::id, std::shared_ptr<std::map<std::string, std::shared_ptr<void>>>> ThreadScopeInstanceFactory::_threads;
__declspec(thread) std::map<std::string, std::shared_ptr<void>> *ThreadScopeInstanceFactory::_instances(__nullptr);

ThreadScopeInstanceFactory::ThreadScopeInstanceFactory() :
	  _mutex()
{
}

ThreadScopeInstanceFactory::~ThreadScopeInstanceFactory()
{
	_instances = __nullptr;
	_threads.clear();
	_instantiators.clear();
}

void ThreadScopeInstanceFactory::EnsureThreadLocalStorageInstancesCacheExists()
{
	if (_instances == __nullptr)
	{
		std::unique_lock<std::recursive_mutex> lock(_mutex);

		std::thread::id threadId = std::this_thread::get_id();

		auto t = _threads.find(threadId);

		if (t == _threads.end())
		{
			std::shared_ptr<std::map<std::string, std::shared_ptr<void>>> threadInstances = std::make_shared<std::map<std::string, std::shared_ptr<void>>>();

			_threads[threadId] = threadInstances;

			_instances = threadInstances.get();
		}
		else
		{
			// this happens in the case of thread id re-use..
			// here, we should assume the TLS member is more trustworthy than
			// the value stored in the static map because of thread id re-use

			std::shared_ptr<std::map<std::string, std::shared_ptr<void>>> threadInstances = std::make_shared<std::map<std::string, std::shared_ptr<void>>>();

			_threads[threadId] = threadInstances;

			_instances = threadInstances.get();
		}
	}
}

void ThreadScopeInstanceFactory::SetCreationStrategy(_In_z_ LPCSTR interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator)
{
	_instantiators[interfaceTypeName] = instantiator;
}

std::shared_ptr<void> ThreadScopeInstanceFactory::GetInstance(_In_ const IContainer &container, _In_z_ LPCSTR interfaceTypeName)
{
	std::shared_ptr<void> result;

	EnsureThreadLocalStorageInstancesCacheExists();

	std::map<std::string, std::shared_ptr<void>> &instances = *_instances;

	auto instance = instances.find(interfaceTypeName);

	if (instance == instances.end())
	{
		auto instantiator = _instantiators.find(interfaceTypeName);

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
			auto creator = instantiator->second;

			result = creator->CreateInstance(container);

			instances[interfaceTypeName] = result;
		}
	}
	else
	{
		result = instance->second;
	}

	return result;
}

void ThreadScopeInstanceFactory::RemoveInstance(_In_z_ LPCSTR interfaceTypeName)
{
	if (_instances != __nullptr)
	{
		std::unique_lock<std::recursive_mutex> lock(_mutex);

		_instances->erase(interfaceTypeName);
	}
}

void ThreadScopeInstanceFactory::Remove(_In_z_ LPCSTR interfaceTypeName)
{
	if (_instances != __nullptr)
	{
		std::unique_lock<std::recursive_mutex> lock(_mutex);

		_instances->erase(interfaceTypeName);
		_instantiators.erase(interfaceTypeName);
	}
}
