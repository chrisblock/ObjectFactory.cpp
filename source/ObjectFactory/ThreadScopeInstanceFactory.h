#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "IInstanceFactory.h"

class IContainer;
class IInstantiator;

class ThreadScopeInstanceFactory : public IInstanceFactory
{
public:
	ThreadScopeInstanceFactory();
	ThreadScopeInstanceFactory(const ThreadScopeInstanceFactory &other);
	ThreadScopeInstanceFactory(ThreadScopeInstanceFactory &&other);
	virtual ~ThreadScopeInstanceFactory();

	ThreadScopeInstanceFactory &operator =(ThreadScopeInstanceFactory other);

	friend void swap(ThreadScopeInstanceFactory &left, ThreadScopeInstanceFactory &right);

	virtual void SetCreationStrategy(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator) override;

	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_ const std::string &interfaceTypeName) override;

	virtual void RemoveInstance(_In_ const std::string &interfaceTypeName) override;

	virtual void Remove(_In_ const std::string &interfaceTypeName) override;

	virtual std::vector<RegisteredComponent> GetRegisteredComponents() const override;

private:
	static thread_local std::unordered_map<std::string, std::shared_ptr<void>> _instances;
	std::unordered_map<std::string, std::shared_ptr<IInstantiator>> _instantiators;
};

void swap(ThreadScopeInstanceFactory &left, ThreadScopeInstanceFactory &right);
