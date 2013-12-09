#pragma once

#include <map>
#include <string>

#include "IInstanceFactory.h"

class IInstantiator;

class TransientInstanceFactory : public IInstanceFactory
{
public:
	TransientInstanceFactory();
	virtual ~TransientInstanceFactory();

	virtual void SetCreationStrategy(_In_z_ const char *interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator);

	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_z_ const char *interfaceTypeName);

	virtual void RemoveInstance(_In_z_ const char *interfaceTypeName);

	virtual void Remove(_In_z_ const char *interfaceTypeName);

private:
	std::map<std::string, std::shared_ptr<IInstantiator>> _instantiators;
};
