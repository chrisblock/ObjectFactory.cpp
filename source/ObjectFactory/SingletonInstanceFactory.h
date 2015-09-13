#pragma once

#include <map>
#include <memory>
#include <string>

#include "IInstanceFactory.h"

class IContainer;
class IInstantiator;

class SingletonInstanceFactory : public IInstanceFactory
{
public:
	SingletonInstanceFactory();
	SingletonInstanceFactory(const SingletonInstanceFactory &other);
	SingletonInstanceFactory(SingletonInstanceFactory &&other);
	virtual ~SingletonInstanceFactory();

	SingletonInstanceFactory &operator =(SingletonInstanceFactory other);

	friend void swap(SingletonInstanceFactory &left, SingletonInstanceFactory &right);

	virtual void SetCreationStrategy(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator) override;

	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_ const std::string &interfaceTypeName) override;

	virtual void RemoveInstance(_In_ const std::string &interfaceTypeName) override;

	virtual void Remove(_In_ const std::string &interfaceTypeName) override;

	int GetNumberOfInstances() const;

private:
	mutable std::recursive_mutex _mutex;

	_Guarded_by_(_mutex)
	std::map<std::string, std::shared_ptr<void>> _instances;
	std::map<std::string, std::shared_ptr<IInstantiator>> _instantiators;
};

void swap(SingletonInstanceFactory &left, SingletonInstanceFactory &right);
