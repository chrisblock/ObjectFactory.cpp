#pragma once

#include <map>
#include <memory>
#include <string>
#include <thread>

#include "IInstanceFactory.h"

class IContainer;
class IInstantiator;

class ThreadScopeInstanceFactory : public IInstanceFactory
{
public:
	ThreadScopeInstanceFactory();
	virtual ~ThreadScopeInstanceFactory();

	virtual void SetCreationStrategy(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator);

	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_ const std::string &interfaceTypeName);

	virtual void RemoveInstance(_In_ const std::string &interfaceTypeName);

	virtual void Remove(_In_ const std::string &interfaceTypeName);

private:
	std::recursive_mutex _mutex;
	static std::map<std::thread::id, std::shared_ptr<std::map<std::string, std::shared_ptr<void>>>> _threads;
	static __declspec(thread) std::map<std::string, std::shared_ptr<void>> *_instances;
	std::map<std::string, std::shared_ptr<IInstantiator>> _instantiators;

	void EnsureThreadLocalStorageInstancesCacheExists();
};
