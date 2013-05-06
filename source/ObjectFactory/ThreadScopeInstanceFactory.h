#pragma once

#include <tchar.h>
#include <string>
#include <map>

#include "IInstanceFactory.h"

#include "Mutex.h"
#include "IInstantiator.h"
#include "IContainer.h"

class ThreadScopeInstanceFactory : public IInstanceFactory
{
public:
	ThreadScopeInstanceFactory();
	virtual ~ThreadScopeInstanceFactory();

	virtual void SetCreationStrategy(LPCTSTR interfaceTypeName, const std::shared_ptr<IInstantiator> &instantiator);

	virtual shared_ptr<void> GetInstance(const IContainer &container, LPCTSTR interfaceTypeName);

	virtual void Remove(LPCTSTR interfaceTypeName);

private:
	Mutex _mutex;
	static std::map<DWORD, shared_ptr<std::map<basic_string<TCHAR>, std::shared_ptr<void>>>> _threads;
	static __declspec(thread) std::map<std::basic_string<TCHAR>, std::shared_ptr<void>> *_instances;
	std::map<std::basic_string<TCHAR>, std::shared_ptr<IInstantiator>> _instantiators;

	void EnsureThreadLocalStorageInstancesCacheExists();
};
