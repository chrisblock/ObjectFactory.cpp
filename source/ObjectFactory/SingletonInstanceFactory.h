#pragma once

#include <map>
#include <string>

#include "IInstanceFactory.h"

class IContainer;
class IInstantiator;

class SingletonInstanceFactory : public IInstanceFactory
{
public:
	SingletonInstanceFactory();
	virtual ~SingletonInstanceFactory();

	virtual void SetCreationStrategy(_In_z_ const char *interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator);

	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_z_ const char *interfaceTypeName);

	virtual void RemoveInstance(_In_z_ const char *interfaceTypeName);

	virtual void Remove(_In_z_ const char *interfaceTypeName);

	int GetNumberOfInstances() const;

private:
	std::recursive_mutex _mutex;

	_Guarded_by_(_mutex)
	std::map<std::string, std::shared_ptr<void>> _instances;
	std::map<std::string, std::shared_ptr<IInstantiator>> _instantiators;
};
