#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "IInstanceFactory.h"

class IContainer;
class IInstantiator;
class RegisteredComponent;

class SingletonInstanceFactory : public IInstanceFactory
{
public:
	SingletonInstanceFactory();
	SingletonInstanceFactory(_In_ const SingletonInstanceFactory &other);
	SingletonInstanceFactory(_In_ SingletonInstanceFactory &&other);
	virtual ~SingletonInstanceFactory();

	SingletonInstanceFactory &operator =(_In_ SingletonInstanceFactory other);

	friend void swap(_Inout_ SingletonInstanceFactory &left, _Inout_ SingletonInstanceFactory &right);

	virtual void SetCreationStrategy(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator) override;

	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_ const std::string &interfaceTypeName) override;

	virtual void RemoveInstance(_In_ const std::string &interfaceTypeName) override;

	virtual void Remove(_In_ const std::string &interfaceTypeName) override;

	virtual std::vector<RegisteredComponent> GetRegisteredComponents() const override;

	int GetNumberOfInstances() const;

private:
	mutable std::recursive_mutex _mutex;

	_Guarded_by_(_mutex)
	std::unordered_map<std::string, std::shared_ptr<void>> _instances;
	std::unordered_map<std::string, std::shared_ptr<IInstantiator>> _instantiators;
};

void swap(_Inout_ SingletonInstanceFactory &left, _Inout_ SingletonInstanceFactory &right);
