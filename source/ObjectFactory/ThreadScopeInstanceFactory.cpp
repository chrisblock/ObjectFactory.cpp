#include "stdafx.h"

#include "ThreadScopeInstanceFactory.h"

#include "Exception.h"
#include "Lock.h"

map<DWORD, shared_ptr<map<basic_string<TCHAR>, shared_ptr<void>>>> ThreadScopeInstanceFactory::_threads;
__declspec(thread) map<basic_string<TCHAR>, shared_ptr<void>> *ThreadScopeInstanceFactory::_instances(__nullptr);

ThreadScopeInstanceFactory::ThreadScopeInstanceFactory() :
	  _mutex(FALSE)
{
}

ThreadScopeInstanceFactory::~ThreadScopeInstanceFactory()
{
	_instances = __nullptr;
	_threads.clear();
	_instanceCreators.clear();
}

void ThreadScopeInstanceFactory::EnsureThreadLocalStorageInstancesCacheExists()
{
	if (_instances == __nullptr)
	{
		Lock lock(_mutex);

		DWORD threadId = ::GetCurrentThreadId();

		auto t = _threads.find(threadId);

		if (t == _threads.end())
		{
			shared_ptr<map<basic_string<TCHAR>, shared_ptr<void>>> threadInstances(new map<basic_string<TCHAR>, shared_ptr<void>>());

			_threads[threadId] = threadInstances;

			_instances = threadInstances.get();
		}
		else
		{
			// this happens in the case of thread id re-use..
			// here, we should assume the TLS member is more trustworthy than
			// the value stored in the static map because of thread id re-use

			shared_ptr<map<basic_string<TCHAR>, shared_ptr<void>>> threadInstances(new map<basic_string<TCHAR>, shared_ptr<void>>());

			_threads[threadId] = threadInstances;

			_instances = threadInstances.get();
		}
	}
}

void ThreadScopeInstanceFactory::SetCreationStrategy(LPCTSTR interfaceTypeName, const shared_ptr<IInstantiator> &instanceCreator)
{
	_instanceCreators[interfaceTypeName] = instanceCreator;
}

shared_ptr<void> ThreadScopeInstanceFactory::GetInstance(const IContainer &container, LPCTSTR interfaceTypeName)
{
	shared_ptr<void> result;

	EnsureThreadLocalStorageInstancesCacheExists();

	map<basic_string<TCHAR>, shared_ptr<void>> &instances = *_instances;

	auto instance = instances.find(interfaceTypeName);

	if (instance == instances.end())
	{
		auto instanceCreator = _instanceCreators.find(interfaceTypeName);

		if (instanceCreator == _instanceCreators.end())
		{
			basic_string<TCHAR> message(__LOC__ _T("Could not find instantiator for interface '"));
			message += interfaceTypeName;
			message += _T("'.");

			throw new Exception(message.c_str());
		}
		else
		{
			auto creator = instanceCreator->second;

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

void ThreadScopeInstanceFactory::Remove(LPCTSTR interfaceTypeName)
{
	if (_instances != __nullptr)
	{
		Lock lock(_mutex);

		_instances->erase(interfaceTypeName);
		_instanceCreators.erase(interfaceTypeName);
	}
}
