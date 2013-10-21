#pragma once

#include <tchar.h>
#include <string>
#include <map>

#include "IInstanceFactory.h"

class IContainer;
class IInstantiator;

class ThreadScopeInstanceFactory : public IInstanceFactory
{
public:
	ThreadScopeInstanceFactory();
	virtual ~ThreadScopeInstanceFactory();

	virtual void SetCreationStrategy(_In_z_ LPCSTR interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator);

	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_z_ LPCSTR interfaceTypeName);

	virtual void Remove(_In_z_ LPCSTR interfaceTypeName);

private:
	std::recursive_mutex _mutex;
	static std::map<DWORD, std::shared_ptr<std::map<std::string, std::shared_ptr<void>>>> _threads;
	static __declspec(thread) std::map<std::string, std::shared_ptr<void>> *_instances;
	std::map<std::string, std::shared_ptr<IInstantiator>> _instantiators;

	void EnsureThreadLocalStorageInstancesCacheExists();
};
